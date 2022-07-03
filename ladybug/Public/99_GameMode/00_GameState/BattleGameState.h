// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "BattleGameState.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		TArray<class ABaseCharacter*> myArmy;
	UPROPERTY()
		TArray<class ABaseCharacter*> enemyArmy;

	UPROPERTY()
		TArray<class ABaseCharacter*> deadMyArmy;
	UPROPERTY()
		TArray<class ABaseCharacter*> deadEnemy;

public:
	TArray<class ABaseCharacter*>& GetMyArmy() { return myArmy; }
	TArray<class ABaseCharacter*>& GetEnemyArmy() { return enemyArmy; }

public:
	void AddMyArmy(class ABaseCharacter* unit) { myArmy.Emplace(unit); }
	void AddEnemyArmy(class ABaseCharacter* unit) { enemyArmy.Emplace(unit); }
	void AddDeadMyArmy(class ABaseCharacter* unit);
	void AddDeadEnemy(class ABaseCharacter* unit);

public:
	void RemoveTimer();
};
