// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_TurnToTarget.generated.h"

/**
 * 
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
		class UAnimMontage* turnLeftMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* turnRightMontage;

	UPROPERTY(EditAnywhere)
		float allowableAngle = 5.f;
	UPROPERTY(EditAnywhere)
		float turnMontageAngle = 40.f;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 3.f;


	bool bTick = false;

	UPROPERTY(EditAnywhere)
		bool bTimeLimit = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTimeLimit == true"))
		float limitTimeValue = 0.f;

	float currentTime;
	
protected:
	void Turn();
};
