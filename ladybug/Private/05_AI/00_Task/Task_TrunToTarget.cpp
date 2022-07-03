// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_TrunToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_TrunToTarget::UTask_TrunToTarget()
{
	bNotifyTick = true;
	NodeName = "TurnToTarget";
}
EBTNodeResult::Type UTask_TrunToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackBoardKey()));
	if (target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Turn();

	return EBTNodeResult::InProgress;
}

void UTask_TrunToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (isTick)
	{
		FRotator lookAtRotation = owner->GetActorRotation();
		lookAtRotation.Yaw = (target->GetActorLocation() - owner->GetActorLocation()).Rotation().Yaw;

		float angle = owner->GetActorRotation().Yaw - lookAtRotation.Yaw;

		if (!isInPlace)
		{
			if (FMath::Abs(angle) <= allowableAngle)
			{
				owner->GetMesh()->GetAnimInstance()->StopAllMontages(0.1f);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}

		auto interpRot = FMath::RInterpTo(owner->GetActorRotation(), lookAtRotation, DeltaSeconds, lerpSpeed);
		owner->SetActorRotation(interpRot);

		if (FMath::Abs(angle) <= allowableAngle)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

FName UTask_TrunToTarget::GetSelectedBlackBoardKey() const
{
	return BlackBoardKey.SelectedKeyName;
}
void UTask_TrunToTarget::Turn()
{
	// owner가 타겟을 바라보는 방향
	FRotator lookAtRotation = owner->GetActorRotation();
	lookAtRotation.Yaw = (target->GetActorLocation() - owner->GetActorLocation()).Rotation().Yaw;

	// Turn해야 하는 각도크기(-180 ~ 180)
	float angle = lookAtRotation.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
	{
		angle = angle - 360.f;
	}
	else if (angle < -180)
	{
		angle = angle + 360.f;
	}

	FTimerDelegate TurnTimerDel = FTimerDelegate::CreateUObject(
		this,
		&UTask_TrunToTarget::Turn);

	if (angle >= angleForPlayMontage)
	{
		float time = owner->GetMesh()->GetAnimInstance()->Montage_Play(rightTurnAnim, 1.f, EMontagePlayReturnType::Duration);
		//타이머정보 저장댐
		FTimerHandle TurnTimerHandle;
		owner->GetWorldTimerManager().SetTimer(
			TurnTimerHandle,
			TurnTimerDel,
			time,
			false
		);
	}
	else if (angle <= -angleForPlayMontage)
	{
		float time = owner->GetMesh()->GetAnimInstance()->Montage_Play(leftTurnAnim, 1.f, EMontagePlayReturnType::Duration);

		//타이머정보 저장댐
		FTimerHandle TurnTimerHandle;
		owner->GetWorldTimerManager().SetTimer(
			TurnTimerHandle,
			TurnTimerDel,
			time,
			false
		);
	}
	else
	{
		isTick = true;
	}

}