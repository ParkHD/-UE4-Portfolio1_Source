// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"

bool UDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	if (obj != nullptr)
	{
		AActor* target = Cast<AActor>(obj);
		if (target != nullptr)
		{
			float distance = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(target);
			if (distance <= attackRange)
			{
				return true;
			}
		}
	}
	return false;
}
FString UDecorator_CheckDistance::GetStaticDescription() const
{
	if (IsInversed())
	{
		return "Check distance to target > " + FString::FormatAsNumber(attackRange);
	}
	else
	{
		return "Check distance to target <= " + FString::FormatAsNumber(attackRange);
	}
}

FName UDecorator_CheckDistance::GetSelectedBlackboardKey() const
{
	return BlackBoardKey.SelectedKeyName;
}

