// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_GoAroundTarget.generated.h"

/**
 * Ÿ�� ������ ��ȸ�ϴ� Task
 * �̿ϼ�!!!
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
		float moveSpeed;	// �̵��ӵ�

	// ������ ���������� ���� ����� ��� turn�ִϸ��̼����� �����ϱ� ����
	UPROPERTY(EditAnywhere)
		float angle;

	FVector tempDir;		// �̵��� Vector����
	float coolTime;			// �� �ʵ��� �̵��� ������

	float timer = 0;		// Ÿ�̸�

	int Dir;				// �����¿� �̵�����
};
