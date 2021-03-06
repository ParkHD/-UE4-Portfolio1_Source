// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_DragDrop/DragableWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "03_Widget/01_Inventory/InventoryButtonShadowWidget.h"
#include "03_Widget/02_DragDrop/WidgetDragDropOperation.h"

void UDragableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}
FReply UDragableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UDragableWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// 드래그 되는 쉐도우 위젯 생성
	dragShadowWidget = CreateWidget<UInventoryButtonShadowWidget>(GetOwningPlayer(), dragShadowWidgetClass);
	if (dragShadowWidget != nullptr)
	{
		dragShadowWidget->SetWidgetRef(this);
		dragShadowWidget->SetUp();

		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>
		(UWidgetBlueprintLibrary::CreateDragDropOperation(dragDropOperationClass));
		if (oper != nullptr)
		{
			oper->widgetRef = this;
			// 드래그 시 생성될 비주얼위젯을 넘김
			oper->DefaultDragVisual = dragShadowWidget;
			// 드래그 중심점 설정
			oper->Pivot = EDragPivot::MouseDown;
			OutOperation = oper;
		}
	}
}
