// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"


// ���� ���
UENUM(BlueprintType)
enum class EGameState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	LOSE,
	VICTORY
};

// BattleLevel������ ���Ӹ��
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
		class AActor* playerSpawnLocation;			// �÷��̾ ������ ��ġ
	UPROPERTY()
		class AActor* enemySpawnLocation;			// ���� ������ ��ġ

	UPROPERTY(EditAnywhere)
		float spawnInterval;						// ���� ����
	UPROPERTY(EditAnywhere)
		FString playerSpawnActor;					// �÷��̾ ������ ��ġ�� ��Ÿ���� TargetActor�� �̸�
	UPROPERTY(EditAnywhere)
		FString enemySpawnActor;					// ���� ������ ��ġ�� ��Ÿ���� TargetActor�� �̸�

	UPROPERTY()
		class AWorldPlayerCharacter* worldPlayer;	// �÷��̾��� WorldCharacter
	UPROPERTY()
		class APlayerCharacter* battlePlayer;		// ���� WorldCharacter


protected:
	void SpawnArmy(class AWorldBaseCharacter* baseCharacter, class AActor* locationActor);	// �δ�� ��ȯ
	void RunAI();											// �δ������ AI�� �����Ѵ�.
public:
	void SaveWorld();										// ���� �����͸� �����Ѵ�.
	void OpenWorldLevel();									// WorldLevel�� �̵��Ѵ�.

	void AddDeadMyArmy(class ABaseCharacter* unit);			// GameState�� ���� �Ʊ� ���� �߰�
	void AddDeadEnemyArmy(class ABaseCharacter* unit);		// GameState�� ���� ���� ���� �߰�

	void SetGameState(EGameState gamestate);				// ������� ����

	class AWorldPlayerCharacter* GetWorldPlayerCharacter() { return worldPlayer; }
public:
	void RomoveTimer();
};


