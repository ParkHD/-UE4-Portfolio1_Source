// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/Item/ItemPickUpWidget.h"
#include "Components/TextBlock.h"

void UItemPickUpWidget::SetItemText(const FText itemName)
{
	TextBlock_ItemName->SetText(itemName);
}
