// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_SetActionState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

EBTNodeResult::Type UTask_SetActionState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (bRand)
	{
		// ActionState를 랜덤하게 받아온다.
		int32 randValue = FMath::RandRange(0, (int32)EActionState::MAX - 1);
		AIActionState = (EActionState)randValue;
	}
	// 블랙보드 값에 저장한다.
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)AIActionState);

	AMonsterBaseCharacter* owner = Cast<AMonsterBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		owner->SetActionState(AIActionState);
	}

	return EBTNodeResult::Succeeded;
}