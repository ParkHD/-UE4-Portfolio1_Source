// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "WorldMonAIController.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API AWorldMonAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWorldMonAIController();
protected:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UFUNCTION()
		void OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus);
};
