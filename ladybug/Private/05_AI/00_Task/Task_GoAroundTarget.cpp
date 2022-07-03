// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_GoAroundTarget.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UTask_GoAroundTarget::UTask_GoAroundTarget()
{
	bNotifyTick = true;
	NodeName = "GoAroundTarget";
}

EBTNodeResult::Type UTask_GoAroundTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 이동할 시간 구하기
	coolTime = FMath::FRandRange(2, 4);
	auto owner = OwnerComp.GetAIOwner()->GetPawn<AMonsterBaseCharacter>();
	if (owner != nullptr)
	{
		auto* target = Cast<AMonsterBaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
		if (target != nullptr)
		{
			FVector dir = owner->GetActorLocation() - target->GetActorLocation();

			tempDir = dir;
			tempDir.X = dir.Y;
			tempDir.Y = -dir.X;

			// 이동할 방향 랜덤으로 설정
			Dir = 0;
			Dir = FMath::RandRange(0, 3);
		}
	}
	
	
	return EBTNodeResult::InProgress;
}



void UTask_GoAroundTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	timer += DeltaSeconds;
	// 시간초과되면 종료
	if(coolTime <= timer)
	{
		timer = 0;

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	AMonsterAIController* controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (controller != nullptr)
	{
		AMonsterBaseCharacter* owner = controller->GetPawn<AMonsterBaseCharacter>();
		if (owner != nullptr)
		{
			ABaseCharacter* target = Cast<ABaseCharacter>(controller->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

			if (target != nullptr)
			{
				// 원방향으로 돌기 
				/*FVector dir = owner->GetActorLocation() - target->GetActorLocation();
				FVector dirNormal = dir.GetSafeNormal();
				FVector dirRight = dir;
				dirRight.X = dir.Y;
				dirRight.Y = -dir.X;

				FVector X = 700.f * dirNormal - dir + dirRight.GetSafeNormal();
				owner->GetCharacterMovement()->Velocity = X.GetSafeNormal() * moveSpeed;*/

				FVector dirTarget = owner->GetActorLocation() - target->GetActorLocation();

				// 이동할 방향 구하기
				FVector characterVelo = FVector::ZeroVector;
				switch (Dir)
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

				// 타겟방향 바라보기
				FRotator rotation = (-dirTarget).Rotation();
				FRotator Rotation = FMath::RInterpTo(owner->GetActorRotation(), rotation, DeltaSeconds, 100.f);
				//Rotation.Yaw -= angle;
				owner->SetActorRotation(Rotation);

				// 타겟방향으로 이동
				FVector Velo = FMath::VInterpTo(owner->GetVelocity(), characterVelo.GetSafeNormal() * moveSpeed, DeltaSeconds, 50.f);
				owner->GetCharacterMovement()->Velocity = Velo;
			}
		}
	}
}
