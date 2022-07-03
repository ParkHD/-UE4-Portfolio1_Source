// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/EquipButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "02_Item/Item.h"
#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "03_Widget/02_DragDrop/WidgetDragDropOperation.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

void UEquipButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (backGroundTexture != nullptr)
	{
		Image_BackGround->SetBrushFromTexture(backGroundTexture);
	}
}

void UEquipButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

FReply UEquipButtonWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

FReply UEquipButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 아이템이 있을 때만 드래그 하게 설정
	if (isEmpty)
	{
		return FReply::Handled();
	}
	else
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
}

FReply UEquipButtonWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	if(!isEmpty)
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			auto equipComp = NewObject<UEquipmentComponent>();
			if (GetOwningPlayerPawn()->IsA<APlayerCharacter>())
			{
				equipComp = GetOwningPlayerPawn<APlayerCharacter>()->GetEquipmentComponent();
			}
			else if (GetOwningPlayerPawn()->IsA<AWorldPlayerCharacter>())
			{
				equipComp = GetOwningPlayerPawn<AWorldPlayerCharacter>()->GetEquipmentComponent();
			}

			if(slotIndex < 4)
			{
				equipComp->RemoveWeaponList(slotIndex);
			}
			else
			{
				switch (slotIndex)
				{
				case 4:
					equipComp->UnEquipHelmet();
					break;
				case 5:
					equipComp->UnEquipCape();
					break;
				case 6:
					equipComp->UnEquipCloth();
					break;
				case 7:
					equipComp->UnEquipGlove();
					break;
				case 8:
					equipComp->UnEquipShoes();
					break;
				}
			}
		}
	}
	
	return FReply::Handled(); // 정상처리
}

void UEquipButtonWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UEquipButtonWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (InOperation != nullptr)
	{
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>(InOperation);
		int32 index = Cast<UInventoryButtonWidget>(oper->widgetRef)->GetIndex();
		UE_LOG(LogTemp, Log, TEXT("index %d"), index);

		if (GetOwningPlayerPawn()->IsA<APlayerCharacter>())
		{
			auto owningPlayer = Cast<APlayerCharacter>(GetOwningPlayerPawn());
		}
		else if (GetOwningPlayerPawn()->IsA<AWorldPlayerCharacter>())
		{
			auto owningPlayer = Cast<AWorldPlayerCharacter>(GetOwningPlayerPawn());
			//itemInSlot = owningPlayer->GetInventoryComponent()->GetInventory()[index];
		}
		return true;
	}
	return false;
}

void UEquipButtonWidget::SetUp(UItem* item)
{
	itemInSlot = item;
	if(itemInSlot != nullptr)
	{
		auto itemInfo = itemInSlot->GetItemInfo<FItemInformation>();
		if(itemInfo != nullptr)
		{
			Image_ItemImage->SetBrushFromTexture(itemInfo->item_Image);
			Image_ItemImage->SetVisibility(ESlateVisibility::Visible);
			isEmpty = false;
		}
		else
		{
			Init();
		}
	}
	else
	{
		Init();
	}
}

void UEquipButtonWidget::Init()
{
	itemInSlot = nullptr;
	isEmpty = true;
	Image_ItemImage->SetVisibility(ESlateVisibility::Hidden);
}
