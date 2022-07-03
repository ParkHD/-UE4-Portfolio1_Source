// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_SwapWeapon.h"

#include "AIController.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/01_HumanType/HumanCharacter.h"

UTask_SwapWeapon::UTask_SwapWeapon()
{
	NodeName = "SwapWeapon";

}

EBTNodeResult::Type UTask_SwapWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto owner = OwnerComp.GetAIOwner()->GetPawn<AHumanCharacter>();
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if(attackTypeToSwap == EAttackType::Melee)
	{
		owner->GetEquipmentComponent()->EquipMeleeWeapon();
	}
	else if (attackTypeToSwap == EAttackType::Range)
	{
		owner->GetEquipmentComponent()->EquipRangeWeapon();
	}

	return EBTNodeResult::Succeeded;
}
