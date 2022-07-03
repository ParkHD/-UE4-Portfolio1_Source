// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_FaceOffTarget.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UTask_FaceOffTarget::UTask_FaceOffTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTask_FaceOffTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 방향을 랜덤으로 구한다.
	dir = FMath::RandRange(0, 3);
	auto owner = OwnerComp.GetAIOwner()->GetPawn<AMonsterBaseCharacter>();

	return EBTNodeResult::InProgress;
}
void UTask_FaceOffTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	tempTime += DeltaSeconds;
	auto owner = OwnerComp.GetAIOwner()->GetPawn<AMonsterBaseCharacter>();
	// 시간이 끝나면 종료한다.
	if(timer <= tempTime)
	{
		tempTime = 0;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	if (owner != nullptr)
	{
		// 타겟을 바라보면서 dir 방향으로 이동한다.
		auto* target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
		if (target != nullptr)
		{
			FVector dirTarget = owner->GetActorLocation() - target->GetActorLocation();
			FVector characterVelo = FVector::ZeroVector;

			// dir에 따른 이동 할 방향Vector 구하기
			switch (dir)
			{
			case 0:
				characterVelo = owner->GetActorForwardVector();
				break;
			case 1:
				characterVelo = -owner->GetActorForwardVector();
				break;
			case 2:
				characterVelo = -owner->GetActorRightVector();
				break;
			case 3:
				characterVelo = owner->GetActorRightVector();
				break;
			}

			// 타겟 마주보기
			FRotator rotation = (-dirTarget).Rotation();
			FRotator Rotation = FMath::RInterpTo(owner->GetActorRotation(), rotation, DeltaSeconds, 100.f);
			//Rotation.Yaw -= angle;
			owner->SetActorRotation(Rotation);

			// 이동
			FVector Velo = FMath::VInterpTo(owner->GetVelocity(), characterVelo.GetSafeNormal() * 200.f, DeltaSeconds, 50.f);
			owner->GetCharacterMovement()->Velocity = Velo;
		}
	}

}
