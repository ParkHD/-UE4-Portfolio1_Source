// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_FlyMove.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UTask_FlyMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_FlyMove();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
protected:
	// 비행 속도
	UPROPERTY(EditAnywhere)
		float moveSpeed;
	// Turn할 때 보간 속도
	UPROPERTY(EditAnywhere)
		float turnSpeed;
	// 멈출 때 브레이크 보간 속도
	UPROPERTY(EditAnywhere)
		float breakValue;
	// 타겟과의 거리를 어디까지 갈 것 인지
	UPROPERTY(EditAnywhere)
		float accessRange;
};
