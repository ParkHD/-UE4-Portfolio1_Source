// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/01_Decorator/Decorator_CheckSP.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UDecorator_CheckSP::UDecorator_CheckSP()
{
	NodeName = "CheckSP";
}

bool UDecorator_CheckSP::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto obj = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	ABaseCharacter* owner = Cast<ABaseCharacter>(obj);
	if (owner != nullptr)
	{
		// 자신의 스태미너가 충분히 없다면 false
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