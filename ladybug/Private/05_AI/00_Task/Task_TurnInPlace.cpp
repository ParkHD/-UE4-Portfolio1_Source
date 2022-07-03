// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_TurnInPlace.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_TurnInPlace::UTask_TurnInPlace()
{
	bNotifyTick = true;
	NodeName = "TurnInPlace";
}
EBTNodeResult::Type UTask_TurnInPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackBoardKey()));
	if (target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UTask_TurnInPlace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 타겟과의 각도구하기
	FRotator newRotation = owner->GetActorRotation();
	newRotation.Yaw = (target->GetActorLocation() - owner->GetActorLocation()).Rotation().Yaw;
	float angle = newRotation.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
	{
		angle = angle - 360.f;
	}
	else if (angle < -180)
	{
		angle = angle + 360.f;
	}

	// 각도가 허용범위 이내면 종료
	if (FMath::Abs(angle) <= allowableAngle)
	{
		owner->turnDir = ETurnDir::NORMAL;

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		// 캐릭터의 회전방향 변수 설정 -> AnimInstance에서 회전 애니메이션 실행
		if (angle >= allowableAngle)
		{
			owner->turnDir = ETurnDir::RIGHTTURN;
		}
		else if (angle <= -allowableAngle)
		{
			owner->turnDir = ETurnDir::LEFTTURN;
		}
		else
		{
			owner->turnDir = ETurnDir::NORMAL;
		}

		// 실제 캐릭터 회전
		auto interpRot = FMath::RInterpTo(owner->GetActorRotation(), newRotation, DeltaSeconds, turnSpeed);
		owner->SetActorRotation(interpRot);
	}
}
