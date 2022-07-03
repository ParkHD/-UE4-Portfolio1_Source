// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"


// 전투 결과
UENUM(BlueprintType)
enum class EGameState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	LOSE,
	VICTORY
};

// BattleLevel에서의 게임모드
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
		class AActor* playerSpawnLocation;			// 플레이어가 스폰될 위치
	UPROPERTY()
		class AActor* enemySpawnLocation;			// 적이 스폰될 위치

	UPROPERTY(EditAnywhere)
		float spawnInterval;						// 스폰 간격
	UPROPERTY(EditAnywhere)
		FString playerSpawnActor;					// 플레이어가 스폰될 위치를 나타내는 TargetActor의 이름
	UPROPERTY(EditAnywhere)
		FString enemySpawnActor;					// 적이 스폰될 위치를 나타내는 TargetActor의 이름

	UPROPERTY()
		class AWorldPlayerCharacter* worldPlayer;	// 플레이어의 WorldCharacter
	UPROPERTY()
		class APlayerCharacter* battlePlayer;		// 적의 WorldCharacter


protected:
	void SpawnArmy(class AWorldBaseCharacter* baseCharacter, class AActor* locationActor);	// 부대원 소환
	void RunAI();											// 부대원들의 AI를 실행한다.
public:
	void SaveWorld();										// 현재 데이터를 저장한다.
	void OpenWorldLevel();									// WorldLevel로 이동한다.

	void AddDeadMyArmy(class ABaseCharacter* unit);			// GameState에 죽은 아군 유닛 추가
	void AddDeadEnemyArmy(class ABaseCharacter* unit);		// GameState에 죽은 적군 유닛 추가

	void SetGameState(EGameState gamestate);				// 전투결과 설정

	class AWorldPlayerCharacter* GetWorldPlayerCharacter() { return worldPlayer; }
public:
	void RomoveTimer();
};


