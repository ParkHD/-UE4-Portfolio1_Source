// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "02_Item/Item.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "03_Widget/02_DragDrop/WidgetDragDropOperation.h"
#include "03_Widget/06_Battle/ItemInfoWidget.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"


void UInventoryButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 툴팁 만들고 숨기기
	if (tooltip == nullptr)
	{
		tooltip = CreateWidget<UItemInfoWidget>(this, tooltipWidgetClass);
	}
	SetToolTip(tooltip);
	ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);

	Init();
}

void UInventoryButtonWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

}

void UInventoryButtonWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

}

// 아무 마우스 버튼에 대해 적용된다 따라서 구분해줘야함 
FReply UInventoryButtonWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // 정상처리
}
FReply UInventoryButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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
FReply UInventoryButtonWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	// 왼쪽 마우스 클릭인지 검사
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UInventoryComponent* InventoryComponent = NewObject<UInventoryComponent>();
		if (GetOwningPlayerPawn()->IsA<APlayerCharacter>())
		{
			InventoryComponent = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();
		}
		else if (GetOwningPlayerPawn()->IsA<AWorldPlayerCharacter>())
		{
			InventoryComponent = GetOwningPlayerPawn<AWorldPlayerCharacter>()->GetInventoryComponent();
		}
		// 아이템 사용
		InventoryComponent->UseItem(itemIndex);
	}
	return FReply::Handled(); // 정상처리
}
void UInventoryButtonWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}
bool UInventoryButtonWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation != nullptr)
	{
		// 받은 operation을 통해 드래그 된 위젯의 정보를 가져와서 아이템 이동
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>(InOperation);
		int32 index = Cast<UInventoryButtonWidget>(oper->widgetRef)->GetIndex();
		int32 targetIndex = itemIndex;

		if(GetOwningPlayerPawn()->IsA<APlayerCharacter>())
		{
			GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->SwapItem(index, targetIndex);
		}
		if (GetOwningPlayerPawn()->IsA<AWorldPlayerCharacter>())
		{
			GetOwningPlayerPawn<AWorldPlayerCharacter>()->GetInventoryComponent()->SwapItem(index, targetIndex);
		}
		return true;
	}
	return false;
}
void UInventoryButtonWidget::Init()
{
	// 빈 슬롯으로 초기화
	TextBlock_ItemCount->SetText(FText::GetEmpty());
	Image_ItemIcon->SetOpacity(0.f);
	isEmpty = true;
}
void UInventoryButtonWidget::SetUpButton(UItem* item)
{
	// 아이템이 있다면 인벤토리 슬롯 UI 업데이트
	if (item != nullptr)
	{
		TextBlock_ItemCount->SetText(FText::AsNumber(item->GetItemCount()));
		const auto info = item->GetItemInfo<FItemInformation>();
		if(info != nullptr)
		{
			UTexture2D* texture = info->item_Image;

			if (texture != nullptr)
			{
				Image_ItemIcon->SetBrushFromTexture(texture);
				Image_ItemIcon->SetOpacity(1.f);
			}
			tooltip->SetUp(item);
		}
		// 툴팁이 나오게설정
		ToolTipWidget->SetVisibility(ESlateVisibility::Visible);

		isEmpty = false;
	}
	// 아이템이 없다면 슬롯 초기화
	else
	{
		Init();
		// 툴팁이 안 나오게 설정
		ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

FText UInventoryButtonWidget::GetItemCountTextBlock()
{
	return TextBlock_ItemCount->GetText();
}