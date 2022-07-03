// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_SearchTarget.h"

#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "99_GameMode/00_GameState/BattleGameState.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_SearchTarget::UTask_SearchTarget()
{
	NodeName = "SearchTarget";
}

EBTNodeResult::Type UTask_SearchTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto owner = OwnerComp.GetAIOwner()->GetPawn<ABaseCharacter>();
	if(owner != nullptr)
	{
		auto gameState = Cast<ABattleGameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (gameState != nullptr)
		{
			// 자신이 어느 팀인지 확인하고 GameState에서 상대 팀List를 가져온다.
			TArray<ABaseCharacter*> targetList;
			if(owner->GetGenericTeamId().GetId() == 10)
			{
				targetList = gameState->GetEnemyArmy();
			}
			else if(owner->GetGenericTeamId().GetId() == 20)
			{
				targetList = gameState->GetMyArmy();
			}

			// 상대 중에 가장 가까이 있는 적을 찾고 블랙보드값에 넣어준다.
			float minDistance = -1;
			ABaseCharacter* target = nullptr;
			for (auto unit : targetList)
			{
				if (minDistance == -1)
				{
					minDistance = owner->GetDistanceTo(unit);
					target = unit;
					continue;
				}

				if(minDistance > owner->GetDistanceTo(unit))
				{
					minDistance = owner->GetDistanceTo(unit);
					target = unit;
				}
			}
			// 블랙보드에 저장
			OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", target);
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
