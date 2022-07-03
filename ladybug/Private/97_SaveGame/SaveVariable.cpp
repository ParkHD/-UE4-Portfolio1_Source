// Fill out your copyright notice in the Description page of Project Settings.


#include "97_SaveGame/SaveVariable.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"



FSaveCharacterData::FSaveCharacterData(AWorldPlayerCharacter* Player)
{
	// WorldCharacter 저장
	WorldCharacterClass = Player->GetClass();

	// ActorComponent 필요 데이터 저장
	// 부대관리 컴포넌트 데이터 저장
	ArmyComponentData.ArmyList = Player->GetArmyComponent()->GetArmyList();
	// 인벤토리 컴포넌트 데이터 저장
	InvenComponentData.ItemList = Player->GetInventoryComponent()->GetInventory();
	// ActorComponent의 장비 컴포넌트 필요 데이터 저장
	for(int i = 0; i < Player->GetEquipmentComponent()->GetWeaponList().Num(); i++)
	{
		EquipComponentData.WeaponList[i] = Player->GetEquipmentComponent()->GetWeaponList()[i];
	}
	EquipComponentData.ArmorList[0] = Player->GetEquipmentComponent()->GetHelmet();
	EquipComponentData.ArmorList[1] = Player->GetEquipmentComponent()->GetCape();
	EquipComponentData.ArmorList[2] = Player->GetEquipmentComponent()->GetCloth();
	EquipComponentData.ArmorList[3] = Player->GetEquipmentComponent()->GetGlove();
	EquipComponentData.ArmorList[4] = Player->GetEquipmentComponent()->GetShoes();

	// 능력치 컴포넌트 데이터 저장
	StatusComponentData.CharacterStat = Player->GetStatusComponent()->GetStat();
}

FSaveCharacterData::FSaveCharacterData(int32 Index, AWorldMonsterCharacter* Monster)
{
	// WorldCharacter 저장
	WorldCharacterClass = Monster->GetClass();

	// 캐릭터 인덱스 저장
	CharacterIndex = Index;
	// 몬스터를 관리하는 거점Actor의 인덱스
	LocationIndex = Monster->GetSpawnLocationIndex();

	// 부대관리 컴포넌트 데이터 저장
	ArmyComponentData.ArmyList = Monster->GetArmyComponent()->GetArmyList();
}
