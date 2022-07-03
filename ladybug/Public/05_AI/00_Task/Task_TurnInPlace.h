// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_TurnInPlace.generated.h"

/**
 * 제자리에서 회전 Task -> AnimInstance를 이용한 회전
 */
UCLASS()
class LADYBUG_API UTask_TurnInPlace : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_TurnInPlace();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
		struct FBlackboardKeySelector BlackBoardKey;

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;

	UPROPERTY(EditAnywhere)
		float allowableAngle = 0.f;			// 허용가능한 타겟과의 각도
	UPROPERTY(EditAnywhere)
		float turnSpeed;					// 회전 보간 속도
public:
	FName GetSelectedBlackBoardKey() { return BlackBoardKey.SelectedKeyName; }
};
