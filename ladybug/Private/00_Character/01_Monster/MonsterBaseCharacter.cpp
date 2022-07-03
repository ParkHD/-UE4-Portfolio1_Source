// Fill out your copyright notice in the Description page of Project Settings.

#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "Components/WidgetComponent.h"

#include "00_Character/01_Monster/MonsterAIController.h"
#include "BrainComponent.h"

#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "00_Character/00_Player/Component/StatusComponent.h"
#include "98_GameInstance/myGameInstance.h"
#include "02_Item/Item.h"

AMonsterBaseCharacter::AMonsterBaseCharacter()
{
	teamIdentyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TeamIdentyParticle"));
	teamIdentyParticle->SetupAttachment(RootComponent);
	teamIdentyParticle->SetRelativeLocation(FVector(0, 0, -150.f));

	GetMesh()->CreateDynamicMaterialInstance(0);
	//GetMesh()->CreateDynamicMaterialInstance(1);

	// 움직일 때 가속 되는 방향으로 Turn되게 설정
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	// 스폰 or 배치 될 때 자동으로 controller부착
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 기본적으로 적으로 팀 설정
	SetGenericTeamId(FGenericTeamId(10));
}
void AMonsterBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnTakeAnyDamage.AddUniqueDynamic(this, &AMonsterBaseCharacter::OnTakeDamageEvent);
}

void AMonsterBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// DataTable에서 데이터를 가져와서 스텟 설정
	SetStat();
}

float AMonsterBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float finalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// HPBar 타이머가 이미 돌고 있다면 타이머 초기화 -> 마지막 Hit 시간을 기준으로 타이머
	if (GetWorld()->GetTimerManager().TimerExists(HPBarTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(HPBarTimerHandle);
	}
	else
	{
		HPBarWidgetComponent->SetVisibility(true);
	}

	// 피격 시 HPBar 위젯 활성화 후 일정 시간 후에 비활성화
	if(ActionState != EActionState::SKILL)
	{
		FTimerDelegate SetVisibilityDelegate = FTimerDelegate::CreateUObject(HPBarWidgetComponent,
			&UWidgetComponent::SetVisibility, false, false);
		GetWorld()->GetTimerManager().SetTimer(
			HPBarTimerHandle,
			SetVisibilityDelegate,
			3.f,
			false);
	}
	
	return finalDamage;
}
void AMonsterBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//// 시체가 서서히 사라지도록 설정
	//if (bodyAppearance)
	//{
	//	currentOpacity = FMath::FInterpTo(currentOpacity, 0.f, DeltaTime, opacityLerpSpeed);
	//	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Appearance"), currentOpacity);
	//	if (currentOpacity <= 0.25f)
	//	{
	//		//Destroy();
	//	}
	//}
}
void AMonsterBaseCharacter::SetMoveState(EMoveState characterState)
{
	MoveState = characterState;
	AMonsterAIController* controller = GetController<AMonsterAIController>();
	if (controller != nullptr)
	{
		switch (characterState)
		{
		case EMoveState::NORMAL:
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			controller->GetBlackboardComponent()->SetValueAsEnum("MoveState", (uint8)EMoveState::NORMAL);
			GetCharacterMovement()->GravityScale = 1.f;
			GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
			break;
		case EMoveState::RUN:
			// 이동속도 증가
			GetCharacterMovement()->MaxWalkSpeed = walkSpeed * 1.4f;
			break;
		case EMoveState::JUMP:
			break;
		case EMoveState::FLY:
			controller->GetBlackboardComponent()->SetValueAsEnum("MoveState", (uint8)EMoveState::FLY);
			if (!GetCharacterMovement()->IsFlying()) // 계속 공중으로 띄어지는 것을 방지
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
				GetCharacterMovement()->GravityScale = 0.f;
				// 캐릭터를 공중으로 띄우기
				GetCharacterMovement()->AddImpulse(FVector(0, 0, 200.f), true);
			}
			break;

		default:
			break;
		}
	}
	
}
void AMonsterBaseCharacter::SetActionState(EActionState actionState)
{
	ActionState = actionState;
	
	AMonsterAIController* controller = GetController<AMonsterAIController>();

	// 블랙보드 Value 설정
	switch (actionState)
	{
	case EActionState::NORMAL:
		controller->GetBlackboardComponent()->SetValueAsEnum("ActionState", (uint8)EActionState::NORMAL);
		break;
	case EActionState::ATTACK:
		controller->GetBlackboardComponent()->SetValueAsEnum("ActionState", (uint8)EActionState::ATTACK);
		break;
	case EActionState::BLOCK:
		controller->GetBlackboardComponent()->SetValueAsEnum("ActionState", (uint8)EActionState::BLOCK);
		break;
	case EActionState::AIM:
		controller->GetBlackboardComponent()->SetValueAsEnum("ActionState", (uint8)EActionState::AIM);
		break;
	default:
		break;
	}
}

void AMonsterBaseCharacter::SetAttackState(EAttackState attackState)
{
	AttackState = attackState;

	AMonsterAIController* controller = GetController<AMonsterAIController>();

	switch (AttackState)
	{
	case EAttackState::READY:
		controller->GetBlackboardComponent()->SetValueAsEnum("AttackState", (uint8)EAttackState::READY);
		break;

	case EAttackState::COOLTIME:
		{
			// 공격 쿨타임을 돌린다.
			controller->GetBlackboardComponent()->SetValueAsEnum("AttackState", (uint8)EAttackState::COOLTIME);
			FTimerDelegate cooltimeDelegate = FTimerDelegate::CreateUObject(this, &AMonsterBaseCharacter::SetAttackState, EAttackState::READY);
			FTimerHandle attackCoolTimer;
			GetWorldTimerManager().SetTimer(attackCoolTimer, cooltimeDelegate, 2.f, false);
		}
		break;
	default:
		break;
	}
}

void AMonsterBaseCharacter::OnDeadEvent()
{
	Super::OnDeadEvent();

	isDead = true;

	// 스턴타이머 초기화
	GetWorldTimerManager().ClearTimer(StunTimerHandle);

	// Behavior Tree 비활성화
	AMonsterAIController* controller = GetController<AMonsterAIController>();
	controller->BrainComponent->StopLogic("Dead");

	// 죽음 애니메이션 재생 및 콜리전 비활성화
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	GetMesh()->PlayAnimation(deadAnimation, false);
	GetMesh()->SetCollisionProfileName(FName("Spectator"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 피아식별 파티클 비활성화
	teamIdentyParticle->SetTemplate(nullptr);

	/*FTimerHandle deadTimer; 
	FTimerDelegate healthBarTimerDel = FTimerDelegate::CreateUObject(
		this,
		&AMonsterBaseCharacter::SetDeadAppearance);
	GetWorldTimerManager().SetTimer(deadTimer, healthBarTimerDel, 3.f, false);*/
}

void AMonsterBaseCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	Super::SetGenericTeamId(TeamID);

	// 팀에 따른 다른 피아식별 파티클 설정
	if (myTeam == 10)
	{
		teamIdentyParticle->SetTemplate(myTeamParticle);
	}
	else if (myTeam == 20)
	{
		teamIdentyParticle->SetTemplate(enemyParticle);
	}
}

void AMonsterBaseCharacter::OnTakeDamageEvent(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	// 대미지 받으면 회전방향 초기화
    turnDir = ETurnDir::NORMAL;
}

void AMonsterBaseCharacter::Attack()
{
	// 공격 몽타주 실행
	float time = GetMesh()->GetAnimInstance()->Montage_Play(GetAttackMontage());

	// 공격 후 공격 쿨타임 설정
	auto info = GetGameInstance<UmyGameInstance>()->GetMonsterInfo(monsterTag.GetTagName());
	if(info != nullptr)
	{
		time = info->monster_Stat.AttackSpeed;
	}
	FTimerHandle attackTimerHandle;
	FTimerDelegate attackDelegate = FTimerDelegate::CreateUObject(this, &ABaseCharacter::SetActionState, EActionState::NORMAL);
	GetWorld()->GetTimerManager().SetTimer(
		attackTimerHandle,
		attackDelegate,
		time,
		false);
}

void AMonsterBaseCharacter::TakeStun(float StunTime)
{
	// 보스는 스턴을 맞지 않는다
	if(!isBoss)
	{
		// 로직 멈추기
		AMonsterAIController* controller = GetController<AMonsterAIController>();
		controller->BrainComponent->StopLogic("Hit");

		// 마지막 스턴을 기준으로 타이머 시간 설정
		if (GetWorldTimerManager().TimerExists(StunTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(StunTimerHandle);
		}

		// 죽지 않았다면 일정 시간 후에 로직 재시작 타이머 설정
		if(!isDead)
		{
			FTimerDelegate hitDelegate;
			hitDelegate.BindUObject(controller->BrainComponent, &UBrainComponent::StartLogic);
			GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, StunTime, false);
		}
	}
}

void AMonsterBaseCharacter::SetStat()
{
	statusComponent->SetBattleCharacterStat(GetGameInstance<UmyGameInstance>()->GetMonsterInfo(monsterTag.GetTagName())->monster_Stat);
}

float AMonsterBaseCharacter::GetMoveDirection()
{
	// 캐릭터의 이동방향을 구하고 atan를 이용하여 이동방향의 각도를 구한다.
	float x = GetVelocity().Y;
	float y = GetVelocity().X;

	float moveDirection = FMath::Atan2(x, y);
	moveDirection = FMath::RadiansToDegrees(moveDirection);

	moveDirection -= GetActorRotation().Yaw;

	// 각도를 -180 ~ 180으로 설정
	if (moveDirection > 180.0f)
	{
		moveDirection -= 360.0f;
	}
	else if (moveDirection < -180.0f)
	{
		moveDirection += 360.0f;
	}

	return moveDirection;
}
