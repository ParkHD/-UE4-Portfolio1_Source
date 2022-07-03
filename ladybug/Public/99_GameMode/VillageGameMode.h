// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VillageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API AVillageGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void StartPlay()override;
protected:
	UPROPERTY()
		class AWorldPlayerCharacter* worldPlayer;
	UPROPERTY()
		class APlayerCharacter* battlePlayer;
	UPROPERTY()
		class ACustomController* controller;

	UPROPERTY(EditAnywhere)
		FString playerSpawnLocation;
	UPROPERTY(EditAnywhere)
		FString unitShopNPCLocation;
	UPROPERTY(EditAnywhere)
		FString EquipmentShopNPCLocation;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ANPCCharacter> npcCharacter;
public:
	class AWorldPlayerCharacter* GetWorldPlayerCharacter() { return worldPlayer; }
public:
	void SaveWorld();
	void OpenWorldLevel();
};
