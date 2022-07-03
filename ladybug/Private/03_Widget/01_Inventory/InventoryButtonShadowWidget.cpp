// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryButtonShadowWidget.h"

#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInventoryButtonShadowWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryButtonShadowWidget::SetUp()
{
	UInventoryButtonWidget* owner = Cast<UInventoryButtonWidget>(widgetRef);

	TextBlock_ItemCount->SetText(owner->GetItemCountTextBlock());
	Image_ItemIcon->SetBrush(owner->GetItemIconTexture()->Brush);
	SetRenderOpacity(0.5f);
}