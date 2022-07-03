// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
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

public:
	UFUNCTION()
	void OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnPerceptionUpdatedEvent(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
		void SetStatusOnBlackBoard(class UStatusComponent* statusComponent);
};
