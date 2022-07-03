// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WorldGameMode.generated.h"

/**
 * WorldLevel에서 사용할 게임모드
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
	void OpenBattleLevel(class AWorldMonsterCharacter* BattleTarget);	// 전장으로 이동
	void OpenVillageLevel(FName VillageTagName);						// 마을로 이동
protected:
	void SaveWorld(FName VillageTagName);								// 마을로 이동 시 데이터 저장
	void SaveWorld(class AWorldMonsterCharacter* BattleTarget);			// 전장으로 이동 시 데이터 저장
	void LoadWorld();													// 데이터 불러오기
};
