// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_SetAttackType.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_SetAttackType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 블랙보드 값 변경
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum("AttackType", (uint8)AttackState);

	AMonsterBaseCharacter* owner = Cast<AMonsterBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	return EBTNodeResult::Succeeded;
}
