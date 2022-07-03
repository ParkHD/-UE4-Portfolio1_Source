// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_FaceOffTarget.generated.h"

/*
 * 타겟과 일정거리로 대치하는 Task
 * 아직 미완성!
 */
UCLASS()
class LADYBUG_API UTask_FaceOffTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_FaceOffTarget();


protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	int dir = 0;			// 상하좌우 이동 할 방향
	float timer = 2;		// 몇 초동안 이동할 것인지

	float tempTime = 0;		// 타이머 계산용
};

