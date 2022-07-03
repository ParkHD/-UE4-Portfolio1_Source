// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VillageGameMode.generated.h"

/**
 * VillageLevel���� ����� GameMode
 */
UCLASS()
class LADYBUG_API AVillageGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void StartPlay()override;
protected:
	UPROPERTY()
		class AWorldPlayerCharacter* worldPlayer;		// �÷��̾��� WorldCharacter(��ü) ������ �������ִ�.
	UPROPERTY()
		class APlayerCharacter* battlePlayer;			// �÷��̾ ������ BattleCharacter�̴�.
	UPROPERTY()
		class ACustomController* controller;

	UPROPERTY(EditAnywhere)
		FString playerSpawnLocation;					// �÷��̾ ������ ��ġ�� ��Ÿ�� TargetActor�� ���ڿ�
	UPROPERTY(EditAnywhere)
		FString unitShopNPCLocation;					// ���ֻ��� NPC�� ������ ��ġ�� ��Ÿ�� TargetActor�� ���ڿ�
	UPROPERTY(EditAnywhere)
		FString EquipmentShopNPCLocation;				// ������ NPC�� ������ ��ġ�� ��Ÿ�� TargetActor�� ���ڿ�

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ANPCCharacter> npcCharacter;	// NPCĳ���� ����
public:
	class AWorldPlayerCharacter* GetWorldPlayerCharacter() { return worldPlayer; }
public:
	void SaveWorld();			// �����͸� �����Ѵ�
	void OpenWorldLevel();		// WorldLevel�� �̵�
};
