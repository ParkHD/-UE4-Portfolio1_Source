// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VillageGameMode.generated.h"

/**
 * VillageLevel에서 사용할 GameMode
 */
UCLASS()
class LADYBUG_API AVillageGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void StartPlay()override;
protected:
	UPROPERTY()
		class AWorldPlayerCharacter* worldPlayer;		// 플레이어의 WorldCharacter(본체) 정보를 가지고있다.
	UPROPERTY()
		class APlayerCharacter* battlePlayer;			// 플레이어가 조종할 BattleCharacter이다.
	UPROPERTY()
		class ACustomController* controller;

	UPROPERTY(EditAnywhere)
		FString playerSpawnLocation;					// 플레이어가 스폰될 위치를 나타낼 TargetActor의 문자열
	UPROPERTY(EditAnywhere)
		FString unitShopNPCLocation;					// 유닛상점 NPC가 스폰될 위치를 나타낼 TargetActor의 문자열
	UPROPERTY(EditAnywhere)
		FString EquipmentShopNPCLocation;				// 장비상점 NPC가 스폰될 위치를 나타낼 TargetActor의 문자열

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ANPCCharacter> npcCharacter;	// NPC캐릭터 외형
public:
	class AWorldPlayerCharacter* GetWorldPlayerCharacter() { return worldPlayer; }
public:
	void SaveWorld();			// 데이터를 저장한다
	void OpenWorldLevel();		// WorldLevel로 이동
};
