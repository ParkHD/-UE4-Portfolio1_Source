// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_GoAroundTarget.generated.h"

/**
 * 타겟 주위를 배회하는 Task
 * 미완성!!!
 */
UCLASS()
class LADYBUG_API UTask_GoAroundTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_GoAroundTarget();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	//virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	//virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
protected:
	UPROPERTY(EditAnywhere)
		float moveSpeed;	// 이동속도

	// 늑대의 오른쪽으로 가는 모션이 없어서 turn애니메이션으로 조정하기 위함
	UPROPERTY(EditAnywhere)
		float angle;

	FVector tempDir;		// 이동할 Vector방향
	float coolTime;			// 몇 초동안 이동할 것인지

	float timer = 0;		// 타이머

	int Dir;				// 상하좌우 이동방향
};
