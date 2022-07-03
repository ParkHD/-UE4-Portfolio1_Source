// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterAIController.generated.h"


// Monster BattleCharacter's controller
UCLASS()
class LADYBUG_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();
protected:
	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
		class AMonsterBaseCharacter* ownerMonster;

	// ��������Ʈ ���ε� �� �Լ�
public:
	// AIPerception
	UFUNCTION()
		void OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus);
	// ������ MP Value ������Ʈ
	UFUNCTION()
		void SetStatusOnBlackBoard(class UStatusComponent* statusComponent);
};
