// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_SetAttackState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

EBTNodeResult::Type UTask_SetAttackState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 블랙보드 값 저장
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum("AttackState", (uint8)AIAttackState);

	AMonsterBaseCharacter* owner = Cast<AMonsterBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		owner->SetAttackState(AIAttackState);
	}

	return EBTNodeResult::Succeeded;
}
