// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckTargetIsDead.h"
#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_CheckTargetIsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Å¸°ÙÀÌ Á×¾ú´Â Áö È®ÀÎ
	ABaseCharacter* target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (target != nullptr)
	{
		return target->IsDead();
	}
	return false;
}

FString UDecorator_CheckTargetIsDead::GetStaticDescription() const
{
	if (IsInversed())
	{
		return "Check Target Is Alive ";
	}
	else
	{
		return "Check Target Is Dead";
	}
}
