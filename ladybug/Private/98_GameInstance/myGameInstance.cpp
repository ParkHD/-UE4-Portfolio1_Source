// Fill out your copyright notice in the Description page of Project Settings.


#include "98_GameInstance/myGameInstance.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"



void UmyGameInstance::Init()
{
	Super::Init();

}

const FMonsterInfo* UmyGameInstance::GetMonsterInfo(FName monsterTag)
{
	if (monsterDataTable != nullptr)
	{
		return monsterDataTable->FindRow<FMonsterInfo>(monsterTag, "");
	}
	return nullptr;
}



const FPotionInformation* UmyGameInstance::GetPotionInfo(FName PotionTag)
{
	if (monsterDataTable != nullptr)
	{
		return potionDataTable->FindRow<FPotionInformation>(PotionTag, "");
	}
	return nullptr;
}

const FVillageInfo* UmyGameInstance::GetVillageInfo(FName VillageTag)
{
	if (villageDataTable != nullptr)
	{
		return villageDataTable->FindRow<FVillageInfo>(VillageTag, "");
	}
	return nullptr;
}

const FNPCInfo* UmyGameInstance::GetNPCInfo(FName NPCTag)
{
	if (npcDataTable != nullptr)
	{
		return npcDataTable->FindRow<FNPCInfo>(NPCTag, "");
	}
	return nullptr;
}

void UmyGameInstance::SetPlayerData(FSaveCharacterData Data)
{
	playerData = Data;
	PlayerInventory = Data.InvenComponentData.ItemList;
	PlayerArmy = Data.ArmyComponentData.ArmyList;
	PlayerWeaponList = Data.EquipComponentData.WeaponList;
	PlayerArmorList = Data.EquipComponentData.ArmorList;
}
