// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WorldGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API AWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void StartPlay()override;
protected:
	UPROPERTY()
		class AWorldPlayerController* controller;

public:
	void OpenBattleLevel(class AWorldMonsterCharacter* BattleTarget);
	void OpenVillageLevel(FName VillageTagName);
protected:
	void SaveWorld(FName VillageTagName);
	void SaveWorld(class AWorldMonsterCharacter* BattleTarget);
	void LoadWorld();
};
