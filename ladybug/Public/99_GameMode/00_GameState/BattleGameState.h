// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "BattleGameState.generated.h"

/**
 * BattleLevel에서 저장할 데이터
 */
UCLASS()
class LADYBUG_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		TArray<class ABaseCharacter*> myArmy;			// 살아있는 플레이어의 부대 List
	UPROPERTY()
	TArray<class ABaseCharacter*> enemyArmy;			// 살아있는 적의 부대 List

	UPROPERTY()
		TArray<class ABaseCharacter*> deadMyArmy;		// 사망한 플레이어의 부대List
	UPROPERTY()
		TArray<class ABaseCharacter*> deadEnemy;		// 사망한 적의 부대 List

public:
	TArray<class ABaseCharacter*>& GetMyArmy() { return myArmy; }
	TArray<class ABaseCharacter*>& GetEnemyArmy() { return enemyArmy; }

public:
	void AddMyArmy(class ABaseCharacter* unit) { myArmy.Emplace(unit); }
	void AddEnemyArmy(class ABaseCharacter* unit) { enemyArmy.Emplace(unit); }
	void AddDeadMyArmy(class ABaseCharacter* unit);
	void AddDeadEnemy(class ABaseCharacter* unit);

public:
	// BattleLevel에 있는 모든 유닛들이 사용하는 스킬타이머를 초기화한다.
	void RemoveTimer();
};
