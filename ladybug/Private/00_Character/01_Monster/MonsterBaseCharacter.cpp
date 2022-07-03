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

	// ������ �� ���� �Ǵ� �������� Turn�ǰ� ����
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	// ���� or ��ġ �� �� �ڵ����� controller����
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// �⺻������ ������ �� ����
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

	// DataTable���� �����͸� �����ͼ� ���� ����
	SetStat();
}

float AMonsterBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float finalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// HPBar Ÿ�̸Ӱ� �̹� ���� �ִٸ� Ÿ�̸� �ʱ�ȭ -> ������ Hit �ð��� �������� Ÿ�̸�
	if (GetWorld()->GetTimerManager().TimerExists(HPBarTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(HPBarTimerHandle);
	}
	else
	{
		HPBarWidgetComponent->SetVisibility(true);
	}

	// �ǰ� �� HPBar ���� Ȱ��ȭ �� ���� �ð� �Ŀ� ��Ȱ��ȭ
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

	//// ��ü�� ������ ��������� ����
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
			// �̵��ӵ� ����
			GetCharacterMovement()->MaxWalkSpeed = walkSpeed * 1.4f;
			break;
		case EMoveState::JUMP:
			break;
		case EMoveState::FLY:
			controller->GetBlackboardComponent()->SetValueAsEnum("MoveState", (uint8)EMoveState::FLY);
			if (!GetCharacterMovement()->IsFlying()) // ��� �������� ������� ���� ����
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
				GetCharacterMovement()->GravityScale = 0.f;
				// ĳ���͸� �������� ����
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

	// ������ Value ����
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
			// ���� ��Ÿ���� ������.
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

	// ����Ÿ�̸� �ʱ�ȭ
	GetWorldTimerManager().ClearTimer(StunTimerHandle);

	// Behavior Tree ��Ȱ��ȭ
	AMonsterAIController* controller = GetController<AMonsterAIController>();
	controller->BrainComponent->StopLogic("Dead");

	// ���� �ִϸ��̼� ��� �� �ݸ��� ��Ȱ��ȭ
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	GetMesh()->PlayAnimation(deadAnimation, false);
	GetMesh()->SetCollisionProfileName(FName("Spectator"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// �Ǿƽĺ� ��ƼŬ ��Ȱ��ȭ
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

	// ���� ���� �ٸ� �Ǿƽĺ� ��ƼŬ ����
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
	// ����� ������ ȸ������ �ʱ�ȭ
    turnDir = ETurnDir::NORMAL;
}

void AMonsterBaseCharacter::Attack()
{
	// ���� ��Ÿ�� ����
	float time = GetMesh()->GetAnimInstance()->Montage_Play(GetAttackMontage());

	// ���� �� ���� ��Ÿ�� ����
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
	// ������ ������ ���� �ʴ´�
	if(!isBoss)
	{
		// ���� ���߱�
		AMonsterAIController* controller = GetController<AMonsterAIController>();
		controller->BrainComponent->StopLogic("Hit");

		// ������ ������ �������� Ÿ�̸� �ð� ����
		if (GetWorldTimerManager().TimerExists(StunTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(StunTimerHandle);
		}

		// ���� �ʾҴٸ� ���� �ð� �Ŀ� ���� ����� Ÿ�̸� ����
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
	// ĳ������ �̵������� ���ϰ� atan�� �̿��Ͽ� �̵������� ������ ���Ѵ�.
	float x = GetVelocity().Y;
	float y = GetVelocity().X;

	float moveDirection = FMath::Atan2(x, y);
	moveDirection = FMath::RadiansToDegrees(moveDirection);

	moveDirection -= GetActorRotation().Yaw;

	// ������ -180 ~ 180���� ����
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
