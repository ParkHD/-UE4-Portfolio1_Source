// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_SetPatrolLocation.h"

#include "AIController.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_SetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AWorldMonsterCharacter* owner = Cast<AWorldMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	FVector center = owner->GetSpawnLocation();
	float patrolX = FMath::RandRange(center.X - patrolRadius, center.X + patrolRadius);
	float patrolY = FMath::RandRange(center.Y - patrolRadius, center.Y + patrolRadius);
	FVector patrolVector = FVector(patrolX, patrolY, center.Z);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolLocation", patrolVector);

	return EBTNodeResult::Succeeded;
}
