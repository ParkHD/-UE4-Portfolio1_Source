// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckDegree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"

bool UDecorator_CheckDegree::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	if (obj != nullptr)
	{
		
		AActor* target = Cast<AActor>(obj);
		if (target != nullptr)
		{
			// Ÿ�ٰ��� ������ ���Ѵ�.
			FRotator newRotate = (target->GetActorLocation() - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()).Rotation();
			float angle = newRotate.Yaw - OwnerComp.GetAIOwner()->GetPawn()->GetActorRotation().Yaw;
			if (angle > 180)
			{
				angle = angle - 360.f;
			}
			else if (angle < -180)
			{
				angle = angle + 360.f;
			}

			// Ÿ�ٰ��� ������ attackRange���� ������ true
			if (FMath::Abs(angle) <= attackRange)
			{
				return true;
			}
		}
	}
	return false;
}
FString UDecorator_CheckDegree::GetStaticDescription() const
{
	if (IsInversed())
	{
		return "Check Degree to target > " + FString::FormatAsNumber(attackRange);
	}
	else
	{
		return "Check Degree to target <= " + FString::FormatAsNumber(attackRange);
	}
}

FName UDecorator_CheckDegree::GetSelectedBlackboardKey() const
{
	return BlackBoardKey.SelectedKeyName;
}
