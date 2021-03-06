// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckTargetDead.h"

#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_CheckTargetDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// 현재 나의 블랙보드 Target값이 죽었는지 확인
	ABaseCharacter* target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if(target != nullptr)
	{
		return target->IsDead();
	}
	return false;
}

FString UDecorator_CheckTargetDead::GetStaticDescription() const
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
