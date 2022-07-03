// Fill out your copyright notice in the Description page of Project Settings.
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

#include "03_Widget/03_Character/HPBarWidget.h"
#include "Components/WidgetComponent.h"

#include "00_Character/02_Component/SkillComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "08_Monster/Monster.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "99_GameMode/BattleGameMode.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "98_GameInstance/myGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#define ORIGINAL_WALK_SPEED 300;															
#define ORIGINAL_RUN_SPEED 600;		

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
	statusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("Status"));
	skillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SKillComponent"));

	WeaponChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChildActorComponent->SetupAttachment(GetMesh(), FName("Weapon_Socket"));

	ShieldChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Shield"));
	ShieldChildActorComponent->SetupAttachment(GetMesh(), FName("Shield_Socket"));

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	AIPerceptionStimuliSourceComponent->bAutoRegister = true;
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());

	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetDrawSize(FVector2D(100.f, 10.f));
	HPBarWidgetComponent->SetupAttachment(RootComponent);
	HPBarWidgetComponent->SetVisibility(false);

	armyComponent = CreateDefaultSubobject<UArmyComponent>(TEXT("ArmyComponent"));

	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	GetMesh()->SetCollisionProfileName("BattleCharacter");

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
}
// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetMesh()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseCharacter::OnMeshComponentOvelapEvent);
	OnDead.AddUniqueDynamic(this, &ABaseCharacter::OnDeadEvent);

}


float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	auto finalHitMontage = hitMontage;
	if(GetMoveState() == EMoveState::FLY)
	{
		finalHitMontage = hitOnFlyMontage;
	}

	float finalDamage = DamageAmount;
	finalDamage = FMath::Clamp(finalDamage - statusComponent->GetStat().Defence, 5.f, finalDamage - statusComponent->GetStat().Defence);

	if (GetActionState() == EActionState::BLOCK)
	{
		if (statusComponent->CheckStamina(finalDamage))
		{
			statusComponent->AddStamina(-finalDamage);

			finalDamage = 0;
			finalHitMontage = hitBlockMontage;
		}
		else
		{
			SetActionState(EActionState::NORMAL);
		}
		isBlockSuccess = true;
	}
	else
	{
		if (ActionState == EActionState::SKILL)
		{
			finalHitMontage = nullptr;
		}

		if (hitSound != nullptr)
		{
			FSoundAttenuationSettings setting;
			setting.FalloffDistance = falloffDistance;
			USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
			soundAtt->Attenuation = setting;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetActorLocation(),
				FRotator::ZeroRotator,
				1.f, 1.f, 0.f, soundAtt);
		}
		isBlockSuccess = false;
	}

	if(finalHitMontage != nullptr)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(finalHitMontage);
	}

	statusComponent->AddHP(-finalDamage);
	

	if (isBlockSuccess)
	{
		//SetActionState(EActionState::NORMAL);
		isBlockSuccess = false;
	}
	else
	{
		TakeStun(0.5f);
	}

	return finalDamage;
}

void ABaseCharacter::TakeDamageType(EDamageType damageType, float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser, bool bBreakBlock)
{
	if (ActionState == EActionState::BLOCK)
	{
		if (bBreakBlock)
		{
			SetActionState(EActionState::NORMAL);
		}
	}

	float damage = TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	GetStatusComponent()->AddMP(10);
	if(damageType == EDamageType::NORMAL)
	{
		if(damage > 0)
			Cast<ABaseCharacter>(DamageCauser)->GetStatusComponent()->AddMP(20);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetMoveState(EMoveState characterState)
{
	MoveState = characterState;

	switch (characterState)
	{
	case EMoveState::NORMAL:
		GetCharacterMovement()->MaxWalkSpeed = ORIGINAL_WALK_SPEED;
		break;
	case EMoveState::RUN:
		GetCharacterMovement()->MaxWalkSpeed = ORIGINAL_RUN_SPEED;
		break;
	case EMoveState::JUMP:
		break;
	case EMoveState::FLY:

		break;
	default:
		break;
	}
}

void ABaseCharacter::SetActionState(EActionState actionState)
{
	ActionState = actionState;

	switch (actionState)
	{
	case EActionState::NORMAL:
		break;
	case EActionState::ATTACK:
		break;
	case EActionState::BLOCK:
		break;
	default:
		break;
	}
}

void ABaseCharacter::SetAttackState(EAttackState attackState)
{
	AttackState = attackState;
}

bool ABaseCharacter::AddHitActors(AActor* target)
{
	if (hitActors.Contains(target))
	{
		return false;
	}
	hitActors.Emplace(target);
	return true;
}

void ABaseCharacter::ClearHitActors()
{
	hitActors.Empty();
}

void ABaseCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	myTeam = TeamID;

}

void ABaseCharacter::TakeStun(float StunTime)
{
}

void ABaseCharacter::OnMeshComponentOvelapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABaseCharacter>())
	{
		FRotator lookAtRot = GetActorRotation();
		lookAtRot = (OtherComp->GetComponentLocation()-OverlappedComponent->GetComponentLocation()).Rotation();
		
		FVector directionVector = lookAtRot.Vector() * addforce;
		directionVector.Z = 0.f;

		Cast<ABaseCharacter>(OtherActor)->GetCharacterMovement()->AddImpulse(directionVector, true);
		UE_LOG(LogTemp, Log, TEXT("%s"), *GetName());
	}
}
void ABaseCharacter::OnDeadEvent()
{
	if (myTeam == 10)
	{
		Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddDeadMyArmy(this);
	}
	else if(myTeam == 20)
	{
		Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddDeadEnemyArmy(this);
	}
}