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
		class UDataTable* potionDataTable;		// ���� DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* monsterDataTable;		// ���� DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* villageDataTable;		// ���� DataTable
	UPROPERTY(EditAnywhere)
		class UDataTable* npcDataTable;			// NPC DataTable

	FSaveCharacterData playerData;		// WorldLevel�� �ִ� �÷��̾� ������
	FSaveCharacterData targetData;		// WorldLevel�� �ִ� �÷��̾�� ������ �� ���� ������
	
	TMap<int32, FSaveCharacterData> worldMonsterDatas;	// WorldLevel�� �ִ� ���͵��� ������

	FName VillageNameToEnter;			// WorldLevel���� �÷��̾ ���� �ִ� ������ �±�
public:
	// DataTable���� ���� �˻�
	const FMonsterInfo* GetMonsterInfo(FName monsterTag);
	const FPotionInformation* GetPotionInfo(FName PotionTag);
	const FVillageInfo* GetVillageInfo(FName VillageTag);
	const FNPCInfo* GetNPCInfo(FName NPCTag);

	//class UClass* GetPlayerCharacter() { return playerCharacter; }
	//void SetPlayerCharacter(class UClass* player) { playerCharacter = player; }
	FSaveCharacterData& GetTargetData() { return targetData; }		
	void SetTargetData(FSaveCharacterData Data) { targetData = Data; }				// �� ������ ����

	FSaveCharacterData& GetPlayerData() { return playerData; }
	void SetPlayerData(FSaveCharacterData Data);									// �÷��̾� ������ ����

	TMap<int32, FSaveCharacterData>& GetMonsterData() { return worldMonsterDatas; }

	void AddMonsterData(int32 Index, FSaveCharacterData MonsterData)
	{
		worldMonsterDatas.Add(Index, MonsterData);
		MonsterCharacterClass.Emplace(MonsterData.WorldCharacterClass);
	}
	void RemoveMonsterData(int32 Index) { worldMonsterDatas.Remove(Index); }		// ����List�� �ش� �ε��� ���� ����

	void SetVillageTagName(FName villageTagName) { VillageNameToEnter = villageTagName; }
	FName GetVillageTagName() { return VillageNameToEnter; }
public:
	UPROPERTY()
		TArray<class UItem*> lootItemList;				// ���� �߿� ���� ����ǰ List
public:
	// SetPlayerData�� ���� -> Level�Ѿ�鼭 ������ ���ܼ� �����Ǵ� ���� ����
	UPROPERTY()
		TArray<class UItem*> PlayerInventory;			// �÷��̾��� �κ��丮�ȿ� �ִ� ������ List
	UPROPERTY()
		TArray<class UMonster*> PlayerArmy;				// �÷��̾��� �δ�List
	UPROPERTY()
		TArray<class UWeapon*> PlayerWeaponList;		// �÷��̾��� �����ϰ� �ִ� ���� List
	UPROPERTY()
		TArray<class UArmor*> PlayerArmorList;			// �÷��̾ �����ϰ� �ִ� �� List
	UPROPERTY()
		class UClass* PlayerCharacterClass;				// �÷��̾��� WorldCharacter

	UPROPERTY()
		TArray<class UClass*> MonsterCharacterClass;	// �÷��̾�� ������ �� ���� WorldCharacter
};
