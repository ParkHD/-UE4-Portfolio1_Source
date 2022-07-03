// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_TurnInPlace.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_TurnInPlace::UTask_TurnInPlace()
{
	bNotifyTick = true;
	NodeName = "TurnInPlace";
}
EBTNodeResult::Type UTask_TurnInPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	return EBTNodeResult::InProgress;
}

void UTask_TurnInPlace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FRotator newRotation = owner->GetActorRotation();
	newRotation.Yaw = (target->GetActorLocation() - owner->GetActorLocation()).Rotation().Yaw;

	//UE_LOG(LogTemp, Log, TEXT("%f"), newRotation.Yaw);
	float angle = newRotation.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
	{
		angle = angle - 360.f;
	}
	else if (angle < -180)
	{
		angle = angle + 360.f;
	}


	if (FMath::Abs(angle) <= allowableAngle)
	{
		owner->turnDir = ETurnDir::NORMAL;

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		if (angle >= allowableAngle)
		{
			owner->turnDir = ETurnDir::RIGHTTURN;
		}
		else if (angle <= -allowableAngle)
		{
			owner->turnDir = ETurnDir::LEFTTURN;
		}
		else
		{
			owner->turnDir = ETurnDir::NORMAL;
		}

		auto interpRot = FMath::RInterpTo(owner->GetActorRotation(), newRotation, DeltaSeconds, turnSpeed);
		owner->SetActorRotation(interpRot);
	}
}
