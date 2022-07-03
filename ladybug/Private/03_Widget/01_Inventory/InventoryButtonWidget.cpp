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

	// ���� ����� �����
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

// �ƹ� ���콺 ��ư�� ���� ����ȴ� ���� ����������� 
FReply UInventoryButtonWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // ����ó��
}
FReply UInventoryButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// �������� ���� ���� �巡�� �ϰ� ����
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
	// ���� ���콺 Ŭ������ �˻�
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
		// ������ ���
		InventoryComponent->UseItem(itemIndex);
	}
	return FReply::Handled(); // ����ó��
}
void UInventoryButtonWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}
bool UInventoryButtonWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation != nullptr)
	{
		// ���� operation�� ���� �巡�� �� ������ ������ �����ͼ� ������ �̵�
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
	// �� �������� �ʱ�ȭ
	TextBlock_ItemCount->SetText(FText::GetEmpty());
	Image_ItemIcon->SetOpacity(0.f);
	isEmpty = true;
}
void UInventoryButtonWidget::SetUpButton(UItem* item)
{
	// �������� �ִٸ� �κ��丮 ���� UI ������Ʈ
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
		// ������ �����Լ���
		ToolTipWidget->SetVisibility(ESlateVisibility::Visible);

		isEmpty = false;
	}
	// �������� ���ٸ� ���� �ʱ�ȭ
	else
	{
		Init();
		// ������ �� ������ ����
		ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

FText UInventoryButtonWidget::GetItemCountTextBlock()
{
	return TextBlock_ItemCount->GetText();
}