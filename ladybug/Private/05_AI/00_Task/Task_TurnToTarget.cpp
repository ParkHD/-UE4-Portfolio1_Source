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
	currentTime = 0.f;
	// 이 값들이 왜 저장이 될까 초기화가 안되고..
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

	if (bTimeLimit)
	{
		currentTime += DeltaSeconds;
		if (currentTime >= limitTimeValue)
		{
			owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

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

	if (FMath::Abs(angle) <= allowableAngle)
	{
		UE_LOG(LogTemp, Log, TEXT("angle : %f"), angle);
		owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (bTick)
	{
		FRotator rotation = FMath::RInterpTo(owner->GetActorRotation(), dir, DeltaSeconds, rotationSpeed);
		owner->SetActorRotation(rotation);
	}
}
void UTask_TurnToTarget::Turn()
{
	owner->SetActorRotation(FRotator(0, owner->GetActorRotation().Yaw, 0 ));
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
	if(angle >= turnMontageAngle)
	{
		float playTime = owner->GetMesh()->GetAnimInstance()->Montage_Play(turnRightMontage);
		owner->GetWorld()->GetTimerManager().SetTimer(
			turnTimer,
			turnDelegate,
			playTime,
			false);

	}
	else if (angle <= -turnMontageAngle)
	{
		float playTime = owner->GetMesh()->GetAnimInstance()->Montage_Play(turnLeftMontage);
		owner->GetWorld()->GetTimerManager().SetTimer(
			turnTimer,
			turnDelegate,
			playTime,
			false);

	}
	else
	{
		bTick = true;
		return;
	}
}

