// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Service_CheckDistance.generated.h"

/**
 * 타겟과의 거리를 업데이트하는 서비스
 */
UCLASS()
class LADYBUG_API UService_CheckDistance : public UBTService
{
	GENERATED_BODY()
public:
	UService_CheckDistance();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector Target;	// 타겟
};
