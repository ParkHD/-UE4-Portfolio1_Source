// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Battle/ItemInfoWidget.h"
#include "02_Item/Item.h"
#include "02_Item/ItemTypes.h"
#include "02_Item/00_Equipment/Equipment.h"
#include "03_Widget/06_Battle/ItemSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}
void UItemInfoWidget::SetUp(UItem* item)
{
	Init();
	auto info = item->GetItemInfo<FItemInformation>();
	if (info != nullptr)
	{
		TextBlock_ItemName->SetText(FText::FromString(info->item_Name));
		Image_ItemImage->SetBrushFromTexture(info->item_Image);
		TextBlock_ItemDecription->SetText(FText::FromString(info->item_Description_Long));
		if (info->item_Type == EItemType::EQUIPMENT)
		{
			auto equipItem = Cast<UEquipment>(item);
			if (equipItem != nullptr)
			{
				if (!equipItem->GetStat().MaxHP == 0)
				{
					HorizontalBox_HPStat->SetVisibility(ESlateVisibility::Visible);
					TextBlock_HPStat->SetText(FText::AsNumber(equipItem->GetStat().MaxHP));
				}
				if (!equipItem->GetStat().MaxMP == 0)
				{
					HorizontalBox_MPStat->SetVisibility(ESlateVisibility::Visible);
					TextBlock_MPStat->SetText(FText::AsNumber(equipItem->GetStat().MaxMP));
				}
				if (!equipItem->GetStat().MaxSP == 0)
				{
					HorizontalBox_SPStat->SetVisibility(ESlateVisibility::Visible);
					TextBlock_SPStat->SetText(FText::AsNumber(equipItem->GetStat().MaxSP));
				}
				if (!equipItem->GetStat().Damage == 0)
				{
					HorizontalBox_DamageStat->SetVisibility(ESlateVisibility::Visible);
					TextBlock_DamageStat->SetText(FText::AsNumber(equipItem->GetStat().Damage));
				}
				if (!equipItem->GetStat().Defence == 0)
				{
					HorizontalBox_DefenceStat->SetVisibility(ESlateVisibility::Visible);
					TextBlock_DefenceStat->SetText(FText::AsNumber(equipItem->GetStat().Defence));
				}
			}
		}
	}
}
void UItemInfoWidget::SetUp(class UItemSlotWidget* selectedSlot)
{
	Init();

	auto item = selectedSlot->GetItem();
	if(item != nullptr)
	{
		auto itemInfo = item->GetItemInfo<FItemInformation>();
		if(itemInfo != nullptr)
		{
			TextBlock_ItemName->SetText(FText::FromString(itemInfo->item_Name));
			Image_ItemImage->SetBrushFromTexture(itemInfo->item_Image);
			TextBlock_ItemDecription->SetText(FText::FromString(itemInfo->item_Description_Long));
			if(itemInfo->item_Type == EItemType::EQUIPMENT)
			{
				auto equipItem = Cast<UEquipment>(selectedSlot->GetItem());
				if(equipItem != nullptr)
				{
					if(!equipItem->GetStat().MaxHP == 0)
					{
						HorizontalBox_HPStat->SetVisibility(ESlateVisibility::Visible);
						TextBlock_HPStat->SetText(FText::AsNumber(equipItem->GetStat().MaxHP));
					}
					if (!equipItem->GetStat().MaxMP == 0)
					{
						HorizontalBox_MPStat->SetVisibility(ESlateVisibility::Visible);
						TextBlock_MPStat->SetText(FText::AsNumber(equipItem->GetStat().MaxMP));
					}
					if (!equipItem->GetStat().MaxSP == 0)
					{
						HorizontalBox_SPStat->SetVisibility(ESlateVisibility::Visible);
						TextBlock_SPStat->SetText(FText::AsNumber(equipItem->GetStat().MaxSP));
					}
					if (!equipItem->GetStat().Damage == 0)
					{
						HorizontalBox_DamageStat->SetVisibility(ESlateVisibility::Visible);
						TextBlock_DamageStat->SetText(FText::AsNumber(equipItem->GetStat().Damage));
					}
					if (!equipItem->GetStat().Defence == 0)
					{
						HorizontalBox_DefenceStat->SetVisibility(ESlateVisibility::Visible);
						TextBlock_DefenceStat->SetText(FText::AsNumber(equipItem->GetStat().Defence));
					}
				}
			}
		}
	}
}

void UItemInfoWidget::Init()
{
	TextBlock_ItemDecription->SetText(FText::FromString(""));
	Image_ItemImage->SetBrushFromTexture(nullptr);
	TextBlock_ItemName->SetText(FText::FromString(""));
	for(auto statSlot : VerticalBox_Stat->GetAllChildren())
	{
		statSlot->SetVisibility(ESlateVisibility::Hidden);
	}
}