// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "Decorator_CheckTargetIsDead.generated.h"

/**
 * Å¸°ÙÀÌ Á×¾ú´ÂÁö È®ÀÎ
 */
UCLASS()
class LADYBUG_API UDecorator_CheckTargetIsDead : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
};
