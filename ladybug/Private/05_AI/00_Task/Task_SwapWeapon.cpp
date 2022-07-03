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

	// 입력받은 공격타입에 따라 근거리 또는 원거리 무기 장착
	if(attackTypeToSwap == EAttackType::Melee)
	{
		// 근거리무기 장착
		owner->GetEquipmentComponent()->EquipMeleeWeapon();
	}
	else if (attackTypeToSwap == EAttackType::Range)
	{
		// 원거리무기 장착
		owner->GetEquipmentComponent()->EquipRangeWeapon();
	}

	return EBTNodeResult::Succeeded;
}
