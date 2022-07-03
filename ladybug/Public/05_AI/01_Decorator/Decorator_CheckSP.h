// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "Decorator_CheckSP.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UDecorator_CheckSP : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UDecorator_CheckSP();

protected:
	UPROPERTY(EditAnywhere)
		float stamina = 0.f;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
