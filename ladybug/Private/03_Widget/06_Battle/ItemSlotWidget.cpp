// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Battle/ItemSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "02_Item/Item.h"
#include "02_Item/ItemTypes.h"

FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (item != nullptr)
	{
		OnClickSlot.Broadcast(this);
	}

	return FReply::Handled(); // 정상처리
}
void UItemSlotWidget::SetUp(class UItem* itemclass)
{
	if (itemclass != nullptr)
	{
		// 슬롯에 아이템을 추가하고 아이템 정보에 따라 슬롯위젯 업데이트
		item = itemclass;
		const FItemInformation* itemInfo = item->GetItemInfo<FItemInformation>();
		if (itemInfo != nullptr)
		{
			UTexture2D* texture = itemInfo->item_Image;
			Image_ItemImage->SetBrushFromTexture(texture);

			TextBlock_ItemName->SetText(FText::FromString(itemInfo->item_Name));
			TextBlock_ItemCount->SetText(FText::AsNumber(item->GetItemCount()));

			Image_SelectedFrame->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
