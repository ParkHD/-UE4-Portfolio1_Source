// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckDistanceTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"

bool UDecorator_CheckDistanceTo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if(GetSelectedBlackboardKey() == "Target")
	{
		auto obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
		if (obj != nullptr)
		{
			AActor* target = Cast<AActor>(obj);
			if (target != nullptr)
			{
				float distancefromTarget = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(target);
				if (distancefromTarget <= distance)
				{
					return true;
				}
			}
		}
	}
	else if(GetSelectedBlackboardKey() == "PatrolLocation")
	{
		auto patrolVector = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		FVector spawnVector = OwnerComp.GetAIOwner()->GetPawn<AWorldMonsterCharacter>()->GetSpawnLocation();
		float distancefromTarget = FVector::Distance(spawnVector, patrolVector);
		if (distancefromTarget <= distance)
		{
			return true;
		}
	}
	return false;
}

FString UDecorator_CheckDistanceTo::GetStaticDescription() const
{
	if (bInversed)
	{
		return "Check distance to target > " + FString::FormatAsNumber(distance);
	}
	else
	{
		return "Check distance to target <= " + FString::FormatAsNumber(distance);
	}
}
