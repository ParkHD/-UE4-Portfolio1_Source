// Fill out your copyright notice in the Description page of Project Settings.


#include "06_ProjectileActor/ProjectileActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
// Sets default values
AProjectileActor::AProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;

	sphereComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComponent"));
	sphereComponent->SetCollisionProfileName("NoCollision");
	RootComponent = sphereComponent;

	skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	skeletalMeshComponent->SetCollisionProfileName("NoCollision");
	skeletalMeshComponent->SetupAttachment(RootComponent);

	particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	particleComponent->SetupAttachment(RootComponent);

	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	projectileComponent->ProjectileGravityScale = 0.f;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->SetupAttachment(RootComponent);
	audioComponent->bOverrideAttenuation = true;

	// 이동방향으로 회전
	projectileComponent->bRotationFollowsVelocity = true;
}

void AProjectileActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	sphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileActor::OnComponentBeginOverlapEvent);
	if(bLifeSpan)
	{
		// 생명주기 설정
		SetLifeSpan(lifeSpanValue);
	}
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileActor::Destroyed()
{
	Super::Destroyed();

	auto myCharacter = Cast<ABaseCharacter>(GetOwner());
	if (myCharacter != nullptr)
	{
		hitActors.Empty();
	}
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AProjectileActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto myCharacter = Cast<ABaseCharacter>(GetOwner());
	if (myCharacter != OtherActor)
	{
		if (!hitActors.Contains(OtherActor))
		{
			hitActors.Emplace(OtherActor);
			// overlap 효과 재생
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);

			// 멀티공격이 아니라면 콜리전을 꺼서 다중공격 방지
			if(bHitSingle)
			{
				sphereComponent->SetCollisionProfileName("NoCollision");
				projectileComponent->Velocity = FVector::ZeroVector;
				audioComponent->VolumeMultiplier = 0.f;
			}

			if (OtherActor->IsA<ABaseCharacter>())
			{
				// 캐릭터라면 대미지 주기
				auto targetCharacter = Cast<ABaseCharacter>(OtherActor);
				if (targetCharacter != myCharacter && targetCharacter->GetGenericTeamId() != myCharacter->GetGenericTeamId())
				{
					FDamageEvent damageEvent;
					EDamageType damageType = isSkill ? EDamageType::SKILL : EDamageType::NORMAL;
					targetCharacter->TakeDamageType(damageType, skillDamage
						, damageEvent, myCharacter->GetController(), myCharacter);
				}
			}

			if (bAttachToTarget)
			{
				// 타겟에 붙이기(화살이 꽂히도록)
				this->AttachToComponent(OtherComp, FAttachmentTransformRules::KeepWorldTransform, SweepResult.BoneName);
			}
		}
		
	}
}

void AProjectileActor::TurnOnCollision(bool bTurn)
{
	sphereComponent->SetCollisionProfileName("Weapon");
}