// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckStamina.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UDecorator_CheckStamina::UDecorator_CheckStamina()
{
	NodeName = "CheckStamina";
}

bool UDecorator_CheckStamina::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto obj = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackBoardKey());
	ABaseCharacter* owner = Cast<ABaseCharacter>(obj);
	if (owner != nullptr)
	{
		if (owner->GetStatusComponent()->CheckStamina(stamina))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}