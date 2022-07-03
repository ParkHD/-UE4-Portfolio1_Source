// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_NPC/NPCDialogueWidget.h"
#include "00_Character/03_NPC/NPCCharacter.h"
#include "Components/Button.h"
#include "03_Widget/05_NPC/00_UnitShop/UnitShopWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/CustomController.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "02_Item/Item.h"
#include "03_Widget/06_Battle/ItemManagerWidget.h"
#include "08_Monster/Monster.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"

void UNPCDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_GotoShop->OnClicked.AddUniqueDynamic(this, &UNPCDialogueWidget::OnClickShop);
	Button_ExitDialog->OnClicked.AddUniqueDynamic(this, &UNPCDialogueWidget::OnClickExit);

	OnVisibilityChanged.AddUniqueDynamic(this, &UNPCDialogueWidget::OnVisibilityChangedEvent);
}

void UNPCDialogueWidget::OnClickShop()
{
	if(ownerNPC != nullptr)
	{
		if (shopWidget == nullptr)
		{
			if (UMG_shopWidget != nullptr)
			{
				auto caller = ownerNPC->GetCaller();
				if (caller != nullptr)
				{
					if(UMG_shopWidget->IsChildOf<UUnitShopWidget>())
					{
						shopWidget = CreateWidget<UUserWidget>(caller->GetController<ACustomController>(), UMG_shopWidget);
						auto unitShopWidget = Cast<UUnitShopWidget>(shopWidget);
					
						TArray<UMonster*> shopList;
						for (auto unit : ownerNPC->GetShopList())
						{
							shopList.Emplace(Cast<UMonster>(unit));
						}

						unitShopWidget->Update(shopList, Cast<AWorldPlayerCharacter>(caller->GetWorldBaseCharacter())->GetArmyComponent()->GetArmyList());
						unitShopWidget->SetNPCOwner(ownerNPC);
						unitShopWidget->AddToViewport();
					}
					else if (UMG_shopWidget->IsChildOf<UItemManagerWidget>())
					{
						shopWidget = CreateWidget<UUserWidget>(caller->GetController<ACustomController>(), UMG_shopWidget);
						auto unitShopWidget = Cast<UItemManagerWidget>(shopWidget);

						TArray<UItem*> shopList;
						for (auto item : ownerNPC->GetShopList())
						{
							shopList.Emplace(Cast<UItem>(item));
						}

						unitShopWidget->Update(shopList, Cast<AWorldPlayerCharacter>(caller->GetWorldBaseCharacter())->GetInventoryComponent()->GetInventory());
						unitShopWidget->SetNPCOwner(ownerNPC);
						unitShopWidget->AddToViewport();
					}
				}
			}
		}

		if (shopWidget != nullptr)
		{
			shopWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UNPCDialogueWidget::OnClickExit()
{
	SetVisibility(ESlateVisibility::Hidden);
	ownerNPC->GetCaller()->SetInteract(false);
}

void UNPCDialogueWidget::OnVisibilityChangedEvent(ESlateVisibility visible)
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