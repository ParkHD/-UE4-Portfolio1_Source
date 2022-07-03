// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/02_Service/Service_CheckDistance.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

UService_CheckDistance::UService_CheckDistance()
{
	bNotifyTick = true;
}


void UService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName);
	if(target != nullptr)
	{
		if(OwnerComp.GetAIOwner()->GetPawn()->IsA<AWorldMonsterCharacter>())
		{
			auto worldOwner = OwnerComp.GetAIOwner()->GetPawn<AWorldMonsterCharacter>();
			if (worldOwner != nullptr)
			{
				float distance = FVector::Distance(worldOwner->GetSpawnLocation(),
					Cast<ACharacter>(target)->GetActorLocation());
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat("TargetDistance", distance);
			}
		}
		else if (OwnerComp.GetAIOwner()->GetPawn()->IsA<AMonsterBaseCharacter>())
		{

			auto worldOwner = OwnerComp.GetAIOwner()->GetPawn<AMonsterBaseCharacter>();
			if (worldOwner != nullptr)
			{
				float distance = worldOwner->GetDistanceTo(Cast<ABaseCharacter>(target));
				
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat("TargetDistance", distance);
			}
		}
	}
}
