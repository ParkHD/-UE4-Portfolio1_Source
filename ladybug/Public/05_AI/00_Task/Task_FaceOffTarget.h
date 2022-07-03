// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_FaceOffTarget.generated.h"

/*
 * Ÿ�ٰ� �����Ÿ��� ��ġ�ϴ� Task
 * ���� �̿ϼ�!
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
	int dir = 0;			// �����¿� �̵� �� ����
	float timer = 2;		// �� �ʵ��� �̵��� ������

	float tempTime = 0;		// Ÿ�̸� ����
};

