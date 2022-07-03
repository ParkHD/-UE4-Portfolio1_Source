// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "08_Monster/Monster.h"
#include "02_Item/ItemTypes.h"
#include "10_WorldCharacter/02_StaticActor/00_Village/VillageWorldActor.h"
#include "97_SaveGame/SaveVariable.h"
#include "myGameInstance.generated.h"

// GameInstance 
UCLASS()
class LADYBUG_API UmyGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init() override;

protected:
	// DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* potionDataTable;		// 포션 DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* monsterDataTable;		// 몬스터 DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* villageDataTable;		// 마을 DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* npcDataTable;			// NPC DataTable

	FSaveCharacterData playerData;		// WorldLevel에 있는 플레이어 데이터
	FSaveCharacterData targetData;		// WorldLevel에 있는 플레이어와 전투에 들어갈 적의 데이터
	
	TMap<int32, FSaveCharacterData> worldMonsterDatas;	// WorldLevel에 있던 몬스터들의 데이터

	FName VillageNameToEnter;			// WorldLevel에서 플레이어가 들어가고 있는 마을의 태그
public:
	// DataTable에서 정보 검색
	const FMonsterInfo* GetMonsterInfo(FName monsterTag);
	const FPotionInformation* GetPotionInfo(FName PotionTag);
	const FVillageInfo* GetVillageInfo(FName VillageTag);
	const FNPCInfo* GetNPCInfo(FName NPCTag);

	//class UClass* GetPlayerCharacter() { return playerCharacter; }
	//void SetPlayerCharacter(class UClass* player) { playerCharacter = player; }
	FSaveCharacterData& GetTargetData() { return targetData; }		
	void SetTargetData(FSaveCharacterData Data) { targetData = Data; }				// 적 데이터 저장

	FSaveCharacterData& GetPlayerData() { return playerData; }
	void SetPlayerData(FSaveCharacterData Data);									// 플레이어 데이터 저장

	TMap<int32, FSaveCharacterData>& GetMonsterData() { return worldMonsterDatas; }

	void AddMonsterData(int32 Index, FSaveCharacterData MonsterData)
	{
		worldMonsterDatas.Add(Index, MonsterData);
		MonsterCharacterClass.Emplace(MonsterData.WorldCharacterClass);
	}
	void RemoveMonsterData(int32 Index) { worldMonsterDatas.Remove(Index); }		// 몬스터List중 해당 인덱스 몬스터 삭제

	void SetVillageTagName(FName villageTagName) { VillageNameToEnter = villageTagName; }
	FName GetVillageTagName() { return VillageNameToEnter; }
public:
	UPROPERTY()
		TArray<class UItem*> lootItemList;				// 전투 중에 얻은 전리품 List
public:
	// SetPlayerData로 관리 -> Level넘어가면서 참조가 끊겨서 삭제되는 것을 방지
	UPROPERTY()
		TArray<class UItem*> PlayerInventory;			// 플레이어의 인벤토리안에 있는 아이템 List
	UPROPERTY()
		TArray<class UMonster*> PlayerArmy;				// 플레이어의 부대List
	UPROPERTY()
		TArray<class UWeapon*> PlayerWeaponList;		// 플레이어의 장착하고 있는 무기 List
	UPROPERTY()
		TArray<class UArmor*> PlayerArmorList;			// 플레이어가 장착하고 있는 방어구 List
	UPROPERTY()
		class UClass* PlayerCharacterClass;				// 플레이어의 WorldCharacter

	UPROPERTY()
		TArray<class UClass*> MonsterCharacterClass;	// 플레이어와 전투에 들어갈 적의 WorldCharacter
};
