// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "Decorator_CheckDistanceTo.generated.h"

/**
 * WorldCharacter에서 타겟과의 거리
 */
UCLASS()
class LADYBUG_API UDecorator_CheckDistanceTo : public UBTDecorator_Blackboard
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
protected:
	UPROPERTY(EditAnywhere)
		float distance;				// 거리
	UPROPERTY(EditAnywhere)
		bool bInversed = false;
};
