// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Service_CheckMP.generated.h"

/**
 * 미사용 -> 그냥 StatusComponent에서 MP변동 될 때 마다 블랙보드 업데이트하도록 변경
 * 자신의 MP량 업데이트 하는 서비스
 */
UCLASS()
class LADYBUG_API UService_CheckMP : public UBTService
{
	GENERATED_BODY()
public:
	UService_CheckMP();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector Target;	// MP
};
