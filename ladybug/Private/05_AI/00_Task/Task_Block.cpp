// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_Block.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_Block::UTask_Block()
{
	bNotifyTick = true;
	NodeName = "Block";
}
EBTNodeResult::Type UTask_Block::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	owner = OwnerComp.GetAIOwner()->GetPawn<ABaseCharacter>();
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	owner->SetActionState(EActionState::BLOCK);

	if (bRandom)
	{
		// 방어를 유지할 시간을 Random으로 설정한다.
		blockTime = FMath::FRandRange(1.f, 4.f);
	}
	time = 0.f;

	return EBTNodeResult::InProgress;
}
void UTask_Block::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	time += DeltaSeconds;
	// 시간이 끝나면 방어를 해제하고 종료한다.
	if (time >= blockTime)
	{
		owner->SetActionState(EActionState::NORMAL);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}