// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/BTTask_SetMoveState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

EBTNodeResult::Type UBTTask_SetMoveState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EMoveState type = AIMoveState;

	// 블랙보드 값을 변경해준다.
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)AIMoveState);
	type = AIMoveState;

	// 캐릭터의 MoveState변경
	AMonsterBaseCharacter* owner = Cast<AMonsterBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		owner->SetMoveState(type);
	}

	return EBTNodeResult::Succeeded;
}