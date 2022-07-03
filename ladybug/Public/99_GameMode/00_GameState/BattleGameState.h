// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "BattleGameState.generated.h"

/**
 * BattleLevel���� ������ ������
 */
UCLASS()
class LADYBUG_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		TArray<class ABaseCharacter*> myArmy;			// ����ִ� �÷��̾��� �δ� List
	UPROPERTY()
	TArray<class ABaseCharacter*> enemyArmy;			// ����ִ� ���� �δ� List

	UPROPERTY()
		TArray<class ABaseCharacter*> deadMyArmy;		// ����� �÷��̾��� �δ�List
	UPROPERTY()
		TArray<class ABaseCharacter*> deadEnemy;		// ����� ���� �δ� List

public:
	TArray<class ABaseCharacter*>& GetMyArmy() { return myArmy; }
	TArray<class ABaseCharacter*>& GetEnemyArmy() { return enemyArmy; }

public:
	void AddMyArmy(class ABaseCharacter* unit) { myArmy.Emplace(unit); }
	void AddEnemyArmy(class ABaseCharacter* unit) { enemyArmy.Emplace(unit); }
	void AddDeadMyArmy(class ABaseCharacter* unit);
	void AddDeadEnemy(class ABaseCharacter* unit);

public:
	// BattleLevel�� �ִ� ��� ���ֵ��� ����ϴ� ��ųŸ�̸Ӹ� �ʱ�ȭ�Ѵ�.
	void RemoveTimer();
};
