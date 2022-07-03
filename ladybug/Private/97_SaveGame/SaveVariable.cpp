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
	// WorldCharacter ����
	WorldCharacterClass = Player->GetClass();

	// ActorComponent �ʿ� ������ ����
	// �δ���� ������Ʈ ������ ����
	ArmyComponentData.ArmyList = Player->GetArmyComponent()->GetArmyList();
	// �κ��丮 ������Ʈ ������ ����
	InvenComponentData.ItemList = Player->GetInventoryComponent()->GetInventory();
	// ActorComponent�� ��� ������Ʈ �ʿ� ������ ����
	for(int i = 0; i < Player->GetEquipmentComponent()->GetWeaponList().Num(); i++)
	{
		EquipComponentData.WeaponList[i] = Player->GetEquipmentComponent()->GetWeaponList()[i];
	}
	EquipComponentData.ArmorList[0] = Player->GetEquipmentComponent()->GetHelmet();
	EquipComponentData.ArmorList[1] = Player->GetEquipmentComponent()->GetCape();
	EquipComponentData.ArmorList[2] = Player->GetEquipmentComponent()->GetCloth();
	EquipComponentData.ArmorList[3] = Player->GetEquipmentComponent()->GetGlove();
	EquipComponentData.ArmorList[4] = Player->GetEquipmentComponent()->GetShoes();

	// �ɷ�ġ ������Ʈ ������ ����
	StatusComponentData.CharacterStat = Player->GetStatusComponent()->GetStat();
}

FSaveCharacterData::FSaveCharacterData(int32 Index, AWorldMonsterCharacter* Monster)
{
	// WorldCharacter ����
	WorldCharacterClass = Monster->GetClass();

	// ĳ���� �ε��� ����
	CharacterIndex = Index;
	// ���͸� �����ϴ� ����Actor�� �ε���
	LocationIndex = Monster->GetSpawnLocationIndex();

	// �δ���� ������Ʈ ������ ����
	ArmyComponentData.ArmyList = Monster->GetArmyComponent()->GetArmyList();
}
