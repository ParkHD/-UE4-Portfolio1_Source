// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Service_CheckMP.generated.h"

/**
 * �̻�� -> �׳� StatusComponent���� MP���� �� �� ���� ������ ������Ʈ�ϵ��� ����
 * �ڽ��� MP�� ������Ʈ �ϴ� ����
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
