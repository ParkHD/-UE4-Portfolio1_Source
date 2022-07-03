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
	armyComponent = CreateDefaultSubobject<UArmyComponent>(TEXT("ArmyComponent"));

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

	// 콜리전 설정
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
		finalHitMontage = hitOnFlyMontage;		// 비행중 Hit모션
	}

	// 나의 방어력에 따른 대미지 감소
	float finalDamage = DamageAmount;
	finalDamage = FMath::Clamp(finalDamage - statusComponent->GetStat().Defence, 5.f, finalDamage - statusComponent->GetStat().Defence);

	// 행동 상태에 따른 Damage 설정
	if (GetActionState() == EActionState::BLOCK)
	{
		// 방어 시 스태미너 충분한 지 확인
		if (statusComponent->CheckStamina(finalDamage))
		{
			// 방어 성공 시 스태미너 감소, 대미지 감소, hit모션 설정
			statusComponent->AddStamina(-finalDamage);
			finalDamage = 0;
			finalHitMontage = hitBlockMontage;
			isBlockSuccess = true;
		}
		// 방어 시 충분한 스태미너가 없다면
		else
		{
			// 방어 해제
			SetActionState(EActionState::NORMAL);
			isBlockSuccess = false;
		}
	}
	else if(GetActionState() == EActionState::DODGE)
	{
		// 회피 상태일 때 대미지 소멸
		finalHitMontage = nullptr;
		finalDamage = 0;
	}
	else
	{
		// 스킬 사용 중에는 HitMotion 삭제 -> 스킬사용 중에는 피격모션 없음
		if (ActionState == EActionState::SKILL)
		{
			finalHitMontage = nullptr;
		}

		if (hitSound != nullptr)
		{
			// HitSound설정
			// 일정 거리 이상이면 소리 안들리게 설정
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

	// 피격 몽타주 재생
	if(finalHitMontage != nullptr)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(finalHitMontage);
	}

	// 데미지 적용
	statusComponent->AddHP(-finalDamage);
	
	if (isBlockSuccess)
	{
		//SetActionState(EActionState::NORMAL);
		isBlockSuccess = false;
	}
	else // 방어하지 못했다면 스턴
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
		// 방어를 무시하는 공격을 받았다면 방어 해제
		if (bBreakBlock)
		{
			SetActionState(EActionState::NORMAL);
		}
	}

	float damage = TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 대미지를 입었다면 자신의 MP회복
	GetStatusComponent()->AddMP(10);

	// 기본 공격으로 대미지를 입었다면 상대 MP회복
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

	// 이동 상태에 따른 캐릭터 속도 설정
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
	// 겹친 곳을 기준으로 타겟을 반대 방향으로 밀어내기
	if (OtherActor->IsA<ABaseCharacter>())
	{
		// 방향 구하기
		FRotator lookAtRot = GetActorRotation();
		lookAtRot = (OtherComp->GetComponentLocation()-OverlappedComponent->GetComponentLocation()).Rotation();
		FVector directionVector = lookAtRot.Vector() * addforce;
		directionVector.Z = 0.f;

		// 상대 밀어내기
		Cast<ABaseCharacter>(OtherActor)->GetCharacterMovement()->AddImpulse(directionVector, true);
	}
}
void ABaseCharacter::OnDeadEvent()
{
	// 죽으면 GameMode의 변수에 추가 -> 전투 종료 조건을 검사하기 위함
	if (myTeam == 10)
	{
		Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddDeadMyArmy(this);
	}
	else if(myTeam == 20)
	{
		Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddDeadEnemyArmy(this);
	}
}