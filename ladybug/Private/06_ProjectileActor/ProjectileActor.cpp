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

	projectileComponent->bRotationFollowsVelocity = true;
}

void AProjectileActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	sphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileActor::OnComponentBeginOverlapEvent);
	if(bLifeSpan)
	{
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
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="OverlappedComponent"></param>
			/// <param name="OtherActor"></param>
			/// <param name="OtherComp"></param>
			/// <param name="OtherBodyIndex"></param>
			/// <param name="bFromSweep"></param>
			/// <param name="SweepResult"></param>
			if(bHitSingle)
			{
				sphereComponent->SetCollisionProfileName("NoCollision");
				projectileComponent->Velocity = FVector::ZeroVector;
				audioComponent->VolumeMultiplier = 0.f;
			}

			if (OtherActor->IsA<ABaseCharacter>())
			{
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
				this->AttachToComponent(OtherComp, FAttachmentTransformRules::KeepWorldTransform, SweepResult.BoneName);
			}
		}
		
	}
}

void AProjectileActor::TurnOnCollision(bool bTurn)
{
	sphereComponent->SetCollisionProfileName("Weapon");
}