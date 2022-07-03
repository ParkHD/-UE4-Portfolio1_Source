// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_FlyMove.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


UTask_FlyMove::UTask_FlyMove()
{
	bNotifyTick = true;
	NodeName = "FlyToTarget";
}
EBTNodeResult::Type UTask_FlyMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UTask_FlyMove::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonsterAIController* controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (controller != nullptr)
	{
		AMonsterBaseCharacter* owner = controller->GetPawn<AMonsterBaseCharacter>();
		if (owner != nullptr)
		{
			ABaseCharacter* target = Cast<ABaseCharacter>(controller->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

			if (target != nullptr)
			{
				target->GetCharacterMovement()->Velocity = FVector::ZeroVector;
			}
		}
	}
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UTask_FlyMove::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	AMonsterAIController* controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (controller != nullptr)
	{
		AMonsterBaseCharacter* owner = controller->GetPawn<AMonsterBaseCharacter>();
		if (owner != nullptr)
		{
			ABaseCharacter* target = Cast<ABaseCharacter>(controller->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

			if (target != nullptr)
			{
				target->GetCharacterMovement()->Velocity = FVector::ZeroVector;
			}
		}
	}
}

void UTask_FlyMove::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);


}

void UTask_FlyMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (controller != nullptr)
	{
		AMonsterBaseCharacter* owner = controller->GetPawn<AMonsterBaseCharacter>();
		if (owner != nullptr)
		{
			ABaseCharacter* target = Cast<ABaseCharacter>(controller->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

			if (target != nullptr)
			{
				float distance = owner->GetDistanceTo(target);
				if (distance > accessRange)
				{
					FVector dir = (target->GetActorLocation() - owner->GetActorLocation()).GetUnsafeNormal();
					dir.Z = 0.f; // z축은 고정해서 공중에 있도록
					owner->GetCharacterMovement()->Velocity = dir * moveSpeed;
					FRotator lookAt = FMath::RInterpTo(owner->GetActorRotation(), dir.Rotation(), DeltaSeconds, turnSpeed);
					owner->SetActorRotation(lookAt);
				}
				else
				{
					FVector velocity = FMath::VInterpTo(owner->GetCharacterMovement()->Velocity, FVector::ZeroVector, DeltaSeconds, breakValue);
					owner->GetCharacterMovement()->Velocity = velocity;
					if (owner->GetCharacterMovement()->Velocity.Size() <= 10.f)
					{
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
				}
			}
		}
	}
}
