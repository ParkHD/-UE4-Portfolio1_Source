// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "Decorator_CheckSP.generated.h"

/**
 * 충분한 Stamina가 있는지 확인
 */
UCLASS()
class LADYBUG_API UDecorator_CheckSP : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UDecorator_CheckSP();

protected:
	UPROPERTY(EditAnywhere)
		float stamina = 0.f;	// 허용 스태미너 기준

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
