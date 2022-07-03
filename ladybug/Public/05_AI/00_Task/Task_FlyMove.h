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
	// ���� �ӵ�
	UPROPERTY(EditAnywhere)
		float moveSpeed;
	// Turn�� �� ���� �ӵ�
	UPROPERTY(EditAnywhere)
		float turnSpeed;
	// ���� �� �극��ũ ���� �ӵ�
	UPROPERTY(EditAnywhere)
		float breakValue;
	// Ÿ�ٰ��� �Ÿ��� ������ �� �� ����
	UPROPERTY(EditAnywhere)
		float accessRange;
};
