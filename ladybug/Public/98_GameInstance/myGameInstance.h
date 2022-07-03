// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "08_Monster/Monster.h"
#include "02_Item/ItemTypes.h"
#include "10_WorldCharacter/02_StaticActor/00_Village/VillageWorldActor.h"
#include "97_SaveGame/SaveVariable.h"
#include "myGameInstance.generated.h"


UCLASS()
class LADYBUG_API UmyGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere)
		class UDataTable* potionDataTable;
	UPROPERTY(EditAnywhere)
		class UDataTable* monsterDataTable;
	UPROPERTY(EditAnywhere)
		class UDataTable* villageDataTable;
	UPROPERTY(EditAnywhere)
		class UDataTable* npcDataTable;

	FSaveCharacterData playerData;
	FSaveCharacterData targetData;
	
	TMap<int32, FSaveCharacterData> worldMonsterDatas;

	FName VillageNameToEnter;
public:
	const FMonsterInfo* GetMonsterInfo(FName monsterTag);
	const FPotionInformation* GetPotionInfo(FName PotionTag);
	const FVillageInfo* GetVillageInfo(FName VillageTag);
	const FNPCInfo* GetNPCInfo(FName NPCTag);

	//class UClass* GetPlayerCharacter() { return playerCharacter; }
	//void SetPlayerCharacter(class UClass* player) { playerCharacter = player; }
	FSaveCharacterData& GetTargetData() { return targetData; }
	void SetTargetData(FSaveCharacterData Data) { targetData = Data; }

	FSaveCharacterData& GetPlayerData() { return playerData; }
	void SetPlayerData(FSaveCharacterData Data);

	TMap<int32, FSaveCharacterData>& GetMonsterData() { return worldMonsterDatas; }

	void AddMonsterData(int32 Index, FSaveCharacterData MonsterData)
	{
		worldMonsterDatas.Add(Index, MonsterData);
	}
	void RemoveMonsterData(int32 Index) { worldMonsterDatas.Remove(Index); }

	void SetVillageTagName(FName villageTagName) { VillageNameToEnter = villageTagName; }
	FName GetVillageTagName() { return VillageNameToEnter; }
public:
	UPROPERTY()
		TArray<class UItem*> lootItemList;
public:
	// SetPlayerData·Î °ü¸®
	UPROPERTY()
		TArray<class UItem*> PlayerInventory;
	UPROPERTY()
		TArray<class UMonster*> PlayerArmy;
	UPROPERTY()
		TArray<class UWeapon*> PlayerWeaponList;
	UPROPERTY()
		TArray<class UArmor*> PlayerArmorList;
};
