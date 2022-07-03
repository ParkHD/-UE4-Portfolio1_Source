// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	LOSE,
	VICTORY
};
UCLASS()
class LADYBUG_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void StartPlay()override;

protected:
	UPROPERTY()
		class ACustomController* controller;
	UPROPERTY()
		class ABattleGameState* battleGameState;
	UPROPERTY()
		class AActor* playerSpawnLocation;
	UPROPERTY()
		class AActor* enemySpawnLocation;

	UPROPERTY(EditAnywhere)
		float spawnInterval;
	UPROPERTY(EditAnywhere)
		FString playerSpawnActor;
	UPROPERTY(EditAnywhere)
		FString enemySpawnActor;

	UPROPERTY()
		class AWorldPlayerCharacter* worldPlayer;
	UPROPERTY()
		class APlayerCharacter* battlePlayer;


protected:
	void SpawnArmy(class AWorldBaseCharacter* baseCharacter, class AActor* locationActor);
	void RunAI();
public:
	void SaveWorld();
	void OpenWorldLevel();

	void AddDeadMyArmy(class ABaseCharacter* unit);
	void AddDeadEnemyArmy(class ABaseCharacter* unit);

	void SetGameState(EGameState gamestate);

	class AWorldPlayerCharacter* GetWorldPlayerCharacter() { return worldPlayer; }
public:
	void RomoveTimer();
};


