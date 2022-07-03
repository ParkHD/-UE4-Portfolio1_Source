// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_TagetOff.h"
#include "AIController.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_TagetOff::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AWorldMonsterCharacter* worldOwner = Cast<AWorldMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (worldOwner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// 블랙보드 값 초기화
	OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat("TargetDistance", 0.f);

	return EBTNodeResult::Succeeded;
}
