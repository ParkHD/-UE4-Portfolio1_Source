// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_TurnToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_TurnToTarget::UTask_TurnToTarget()
{
	bNotifyTick = true;
	NodeName = "TurnToTarget";
}
EBTNodeResult::Type UTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	bTick = false;
	currentTime = 0.f;	// �ð� �ʱ�ȭ
	owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Turn();

	return EBTNodeResult::InProgress;
}
void UTask_TurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// �ð� ������ �ִٸ� ���ð��� ������ �����ϰ��ִ� ��Ÿ�ָ� �����ϰ� Task����
	if (bTimeLimit)
	{
		currentTime += DeltaSeconds;
		if (currentTime >= limitTimeValue)
		{
			owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	// Ÿ�ٰ��� ���� ���ϱ�
	FVector dirVector = target->GetActorLocation() - owner->GetActorLocation();
	FRotator dir = owner->GetActorRotation();
	dir.Yaw = dirVector.Rotation().Yaw;
	float angle = dir.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
	{
		angle -= 360.f;
	}
	else if (angle < -180)
	{
		angle += 360.f;
	}

	// Ÿ�ٰ��� ������ ������ ���϶�� ��Ÿ�ָ� �����ϰ� Task����
	if (FMath::Abs(angle) <= allowableAngle)
	{
		owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	// ������ �̿��Ͽ� ȸ��
	if (bTick)
	{
		FRotator rotation = FMath::RInterpTo(owner->GetActorRotation(), dir, DeltaSeconds, rotationSpeed);
		owner->SetActorRotation(rotation);
	}
}
void UTask_TurnToTarget::Turn()
{
	owner->SetActorRotation(FRotator(0, owner->GetActorRotation().Yaw, 0 ));

	// Ÿ�ٰ��� ���� ���ϱ�
	FVector dirVector = target->GetActorLocation() - owner->GetActorLocation();
	FRotator dir = dirVector.Rotation();
	float angle = dir.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
	{
		angle -= 360.f;
	}
	else if (angle < -180)
	{
		angle += 360.f;
	}

	FTimerHandle turnTimer;
	FTimerDelegate turnDelegate = FTimerDelegate::CreateUObject(this, &UTask_TurnToTarget::Turn);
	// ������ ��� �������� �Ѵ´ٸ� ȸ�� ��Ÿ�ָ� ����
	if(angle >= turnMontageAngle)
	{
		float playTime = owner->GetMesh()->GetAnimInstance()->Montage_Play(turnRightMontage);
		// ��Ÿ�� ������ ������ ��ͷ� Turn�Լ� ����
		owner->GetWorld()->GetTimerManager().SetTimer(
			turnTimer,
			turnDelegate,
			playTime,
			false);

	}
	// ������ ��� �������� �Ѵ´ٸ� ȸ�� ��Ÿ�ָ� ����
	else if (angle <= -turnMontageAngle)
	{
		float playTime = owner->GetMesh()->GetAnimInstance()->Montage_Play(turnLeftMontage);
		// ��Ÿ�� ������ ������ ��ͷ� Turn�Լ� ����
		owner->GetWorld()->GetTimerManager().SetTimer(
			turnTimer,
			turnDelegate,
			playTime,
			false);

	}
	// ������ ������ �̳���� �������� ȸ��
	else
	{
		bTick = true;
		return;
	}
}

