// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_Equipment/Weapon.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"

void UWeapon::UseItem(class APlayerCharacter* player)
{
	if(!player->GetEquipmentComponent()->IsWeaponListFull())
	{
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->AddWeaponList(this);
	}
}

void UWeapon::UseItem(AWorldPlayerCharacter* player)
{
	if (!player->GetEquipmentComponent()->IsWeaponListFull())
	{
		player->GetInventoryComponent()->RemoveItem(this);
		player->GetEquipmentComponent()->AddWeaponList(this);
	}
}
