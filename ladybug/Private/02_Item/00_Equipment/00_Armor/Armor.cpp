// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_Equipment/00_Armor/Armor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"

void UArmor::UseItem(APlayerCharacter* player)
{
	switch(GetItemInfo<FArmorInformation>()->armorType)
	{
	case EArmorType::HELMET:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipHelmet(this);
		break;
	case EArmorType::CAPE:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipCape(this);
		break;
	case EArmorType::CLOTH:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipCloth(this);
		break;
	case EArmorType::GLOVE:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipGlove(this);
		break;
	case EArmorType::SHOES:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipShoes(this);
		break;
	}
}

void UArmor::UseItem(AWorldPlayerCharacter* player)
{
	// 장비타입을 구분해준다.
	switch (GetItemInfo<FArmorInformation>()->armorType)
	{
	case EArmorType::HELMET:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipHelmet(this);
		break;
	case EArmorType::CAPE:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipCape(this);
		break;
	case EArmorType::CLOTH:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipCloth(this);
		break;
	case EArmorType::GLOVE:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipGlove(this);
		break;
	case EArmorType::SHOES:
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->EquipShoes(this);
		break;
	}
}
