// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/EquipInventoryWidget.h"
#include "03_Widget/01_Inventory/EquipmentWidget.h"
#include "03_Widget/01_Inventory/InventoryPannelWidget.h"
#include "03_Widget/01_Inventory/InventoryWidget.h"
#include "Components/Button.h"

void UEquipInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Exit->OnClicked.AddUniqueDynamic(this, &UEquipInventoryWidget::OnClickExitButton);
}
void UEquipInventoryWidget::OnChangeVisibility(ESlateVisibility visible)
{
	if (visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = true;
	}
	else if (visible == ESlateVisibility::Hidden)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = false;
	}
}

void UEquipInventoryWidget::UpdateInventory(TArray<UItem*> itemArray)
{
	UMG_Inventory->GetUMG_InventoryPannel()->UpdateButtons(itemArray);
}

void UEquipInventoryWidget::UpdateEquipment(UEquipmentComponent* EquipComp)
{
	UMG_Equipment->UpdateSlot(EquipComp);
}

void UEquipInventoryWidget::UpdateStatInfo(UStatusComponent* StatComp)
{
	UMG_Equipment->UpdateStatInfo(StatComp);
}

void UEquipInventoryWidget::OnClickExitButton()
{
	SetVisibility(ESlateVisibility::Hidden);
}
