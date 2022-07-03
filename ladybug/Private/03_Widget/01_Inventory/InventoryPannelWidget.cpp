// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryPannelWidget.h"
#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/HorizontalBox.h"
#include "02_Item/Item.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"



void UInventoryPannelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto GridChildren = UniformGridPanel_Buttons->GetAllChildren();
	for (int i = 0; i < GridChildren.Num(); i++)
	{
		UHorizontalBox* horizontalBox = Cast<UHorizontalBox>(GridChildren[i]);
		if (horizontalBox != nullptr)
		{
			for (auto j = 0; j < horizontalBox->GetChildrenCount(); j++)
			{
				auto button = Cast<UInventoryButtonWidget>(horizontalBox->GetChildAt(j));
				if (button != nullptr)
				{
					// ½½·ÔÀÇ ÀÎµ¦½º ¼³Á¤
					int32 index = i * horizontalBox->GetChildrenCount() + j;
					button->SetIndex(index);
					inventoryButtons.Add(button);
				}
			}
		}
	}
}


void UInventoryPannelWidget::InitButtons()
{
	for (int i = 0; i < inventoryButtons.Num(); i++)
	{
		inventoryButtons[i]->Init();
	}
}
void UInventoryPannelWidget::UpdateButtons(TArray<class UItem*> itemArray)
{
	for (int i = 0; i < inventoryButtons.Num(); i++)
	{
		inventoryButtons[i]->SetUpButton(itemArray[i]);
	}
}

