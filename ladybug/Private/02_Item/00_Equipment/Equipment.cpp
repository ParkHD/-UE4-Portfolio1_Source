// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_Equipment/Equipment.h"
#include "02_Item/ItemTypes.h"

UEquipment::UEquipment()
{

}

void UEquipment::ItemStatSetUp()
{
	// DataTable에서 아이템 정보를 가져와 범위 내에 랜덤하게 능력치 설정
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
