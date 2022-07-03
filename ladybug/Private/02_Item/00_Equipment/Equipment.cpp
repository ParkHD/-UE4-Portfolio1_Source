// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_Equipment/Equipment.h"
#include "02_Item/ItemTypes.h"

UEquipment::UEquipment()
{

}

void UEquipment::ItemStatSetUp()
{
	auto itemInfo = GetItemInfo<FEquipmentInformation>();
	if (itemInfo != nullptr)
	{
		equipmentStat.MaxHP = FMath::FRandRange(itemInfo->equipmentStatMin.MaxHP, itemInfo->equipmentStatMax.MaxHP);
		equipmentStat.MaxMP = FMath::FRandRange(itemInfo->equipmentStatMin.MaxMP, itemInfo->equipmentStatMax.MaxMP);
		equipmentStat.MaxSP = FMath::FRandRange(itemInfo->equipmentStatMin.MaxSP, itemInfo->equipmentStatMax.MaxSP);
		equipmentStat.Damage = FMath::FRandRange(itemInfo->equipmentStatMin.Damage, itemInfo->equipmentStatMax.Damage);
		equipmentStat.Defence = FMath::FRandRange(itemInfo->equipmentStatMin.Defence, itemInfo->equipmentStatMax.Defence);
	}
}
