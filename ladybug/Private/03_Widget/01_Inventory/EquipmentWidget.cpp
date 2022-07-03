// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/EquipmentWidget.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "02_Item/Item.h"
#include "03_Widget/01_Inventory/EquipButtonWidget.h"
#include "Components/VerticalBox.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "02_Item/00_Equipment/00_Armor/Armor.h"
#include "03_Widget/01_Inventory/StatInfoWidget.h"

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ½½·Ô ÀÎµ¦½º ÃÊ±âÈ­ : 0~3Àº ¹«±â ½½·Ô, 4~8Àº ¹æ¾î±¸ ½½·Ô
	for(int i = 0; i<VerticalBox_WeaponList->GetAllChildren().Num();i++)
	{
		auto slot = Cast<UEquipButtonWidget>(VerticalBox_WeaponList->GetChildAt(i));
		equipSlotList.Emplace(slot);
		slot->SetIndex(i);
	}
	for (int i = 0; i < VerticalBox_ArmorList->GetAllChildren().Num(); i++)
	{
		auto slot = Cast<UEquipButtonWidget>(VerticalBox_ArmorList->GetChildAt(i));
		equipSlotList.Emplace(slot);
		slot->SetIndex(VerticalBox_WeaponList->GetAllChildren().Num() + i);
	}
}

void UEquipmentWidget::UpdateSlot(UEquipmentComponent* EquipComp)
{
	for(int i = 0; i<EquipComp->GetWeaponList().Num(); i++)
	{
		equipSlotList[i]->SetUp(Cast<UItem>(EquipComp->GetWeaponList()[i]));
	}
	
	equipSlotList[4]->SetUp(Cast<UItem>(EquipComp->GetHelmet()));
	equipSlotList[5]->SetUp(Cast<UItem>(EquipComp->GetCape()));
	equipSlotList[6]->SetUp(Cast<UItem>(EquipComp->GetCloth()));
	equipSlotList[7]->SetUp(Cast<UItem>(EquipComp->GetGlove()));
	equipSlotList[8]->SetUp(Cast<UItem>(EquipComp->GetShoes()));
}

void UEquipmentWidget::UpdateStatInfo(UStatusComponent* StatComp)
{
	UMG_StatInfo->Update(StatComp);
}



