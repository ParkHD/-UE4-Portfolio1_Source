// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_TurnToTarget.generated.h"

/**
 * Ÿ�ٰ��� ������ ������ġ �̻��� �� ��Ÿ�ָ� �̿��Ͽ� ȸ�� �ϰ�
 * ������ �Ʒ���� ������ ������ ������ �̿��Ͽ� ĳ���� ȸ���ϴ� Task
 */
UCLASS()
class LADYBUG_API UTask_TurnToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_TurnToTarget();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;


	UPROPERTY(EditAnywhere)
		class UAnimMontage* turnLeftMontage;	// ���� ȸ�� ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* turnRightMontage;	// ������ ȸ�� ��Ÿ��

	UPROPERTY(EditAnywhere)
		float allowableAngle = 5.f;			// Ÿ�ٰ��� ���� ��� ����
	UPROPERTY(EditAnywhere)
		float turnMontageAngle = 40.f;		// ��� ���� ���� �̻��� �� ��Ÿ�ָ� �����Ͽ� ȸ�� �� ���ΰ�
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 3.f;			// ȸ�� ���� �ӵ�


	bool bTick = false;

	UPROPERTY(EditAnywhere)
		bool bTimeLimit = false;			// ȸ���� �� ���� �ð��� �Ѱ��ΰ�? -> ��� ȸ���� �ؼ� ���°��� ����
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTimeLimit == true"))
		float limitTimeValue = 0.f;			// ȸ�� ���ѽð�

	float currentTime;		// Ÿ�̸�
	
protected:
	void Turn();	// ��Ÿ�ָ� �̿��� ȸ��
};
