// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Battle/ItemManagerWidget.h"
#include "Components/TextBlock.h"
#include "00_Character/03_NPC/NPCCharacter.h"
#include "Components/VerticalBox.h"
#include "08_Monster/Monster.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Widget/05_NPC/00_UnitShop/UnitShopInfoWidget.h"
#include "03_Widget/06_Battle/ItemSlotWidget.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "02_Item/Item.h"
#include "03_Widget/06_Battle/ItemInfoWidget.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "98_GameInstance/myGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "99_GameMode/BattleGameMode.h"
#include "99_GameMode/VillageGameMode.h"

void UItemManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_BringIn->OnClicked.AddUniqueDynamic(this, &UItemManagerWidget::OnClickBringIn);
	Button_BringOut->OnClicked.AddUniqueDynamic(this, &UItemManagerWidget::OnClickBringOut);

	Button_CompleteButton->OnClicked.AddUniqueDynamic(this, &UItemManagerWidget::OnClickExit);
	OnVisibilityChanged.AddUniqueDynamic(this, &UItemManagerWidget::OnVisibilityChangedEvent);
}

void UItemManagerWidget::Init()
{
	VerticalBox_TargetList->ClearChildren();
	VerticalBox_MyList->ClearChildren();
	SetSelectedSlot(nullptr);
	UMG_ItemInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UItemManagerWidget::Update(TArray<class UItem*> npcShopList, TArray<class UItem*> myList)
{
	Init();

	if (UMG_ListSlotWidget != nullptr)
	{
		for (class UItem* shopItem : npcShopList)
		{
			if(shopItem != nullptr)
			{
				UItemSlotWidget* itemSlot = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), UMG_ListSlotWidget);

				itemSlot->OnClickSlot.AddUniqueDynamic(this, &UItemManagerWidget::SetSelectedSlot);
				itemSlot->OnClickSlot.AddUniqueDynamic(UMG_ItemInfo, &UItemInfoWidget::SetUp);
				itemSlot->SetUp(shopItem);
				VerticalBox_TargetList->AddChild(itemSlot);
			}
		}
		for (UItem* myItem : myList)
		{
			if(myItem != nullptr)
			{
				UItemSlotWidget* itemSlot = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), UMG_ListSlotWidget);
				itemSlot->OnClickSlot.AddUniqueDynamic(this, &UItemManagerWidget::SetSelectedSlot);
				itemSlot->OnClickSlot.AddUniqueDynamic(UMG_ItemInfo, &UItemInfoWidget::SetUp);
				itemSlot->SetUp(myItem);
				VerticalBox_MyList->AddChild(itemSlot);
			}
		}
	}
}
void UItemManagerWidget::SetSelectedSlot(class UItemSlotWidget* listSlot)
{
	if (selectedSlot != nullptr)
	{
		selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Hidden);
	}

	selectedSlot = listSlot;
	if(listSlot != nullptr)
	{
		selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Visible);
		UMG_ItemInfo->SetVisibility(ESlateVisibility::Visible);
	}
}

void UItemManagerWidget::OnClickExit()
{
	if(UGameplayStatics::GetGameMode(GetWorld())->IsA<ABattleGameMode>())
	{
		auto gameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		auto gameInstance = Cast<UmyGameInstance>(GetGameInstance());
		auto worldPlayer = gameMode->GetWorldPlayerCharacter();
		
		if (worldPlayer != nullptr)
		{
			for (UItem* bringItem : purchaseList)
			{
				worldPlayer->GetInventoryComponent()->AddItem(bringItem);
				gameInstance->lootItemList.Remove(bringItem);
			}
			for (UItem* dropItem : sellList)
			{
				worldPlayer->GetInventoryComponent()->DropItem(dropItem);
				gameInstance->lootItemList.Emplace(dropItem);
			}

			purchaseList.Reset();
			sellList.Reset();
		}
	}
	else if(UGameplayStatics::GetGameMode(GetWorld())->IsA<AVillageGameMode>())
	{
		auto gameMode = Cast<AVillageGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		auto worldPlayer = gameMode->GetWorldPlayerCharacter();
		if(worldPlayer != nullptr && npcOwner != nullptr)
		{
			if (worldPlayer != nullptr)
			{
				for (UItem* bringItem : purchaseList)
				{
					worldPlayer->GetInventoryComponent()->AddItem(bringItem);
					npcOwner->GetShopList().Remove(bringItem);
				}
				for (UItem* dropItem : sellList)
				{
					worldPlayer->GetInventoryComponent()->DropItem(dropItem);
					npcOwner->GetShopList().Emplace(dropItem);
				}
				purchaseList.Reset();
				sellList.Reset();
			}
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemManagerWidget::OnClickBringIn()
{
	if (selectedSlot != nullptr)
	{
		if (!purchaseList.Contains(selectedSlot->GetItem()))
		{
			purchaseList.Emplace(selectedSlot->GetItem());
			sellList.Remove(selectedSlot->GetItem());
			VerticalBox_MyList->AddChildToVerticalBox(selectedSlot);
		}
	}
}
void UItemManagerWidget::OnClickBringOut()
{
	if (selectedSlot != nullptr)
	{
		if (!sellList.Contains(selectedSlot->GetItem()))
		{
			VerticalBox_TargetList->AddChildToVerticalBox(selectedSlot);
			purchaseList.Remove(selectedSlot->GetItem());
			sellList.Emplace(selectedSlot->GetItem());
		}
	}
}

void UItemManagerWidget::OnVisibilityChangedEvent(ESlateVisibility visible)
{
	if (visible == ESlateVisibility::Visible)
	{
	}
	else if (visible == ESlateVisibility::Hidden)
	{
		UMG_ItemInfo->Init();
		UMG_ItemInfo->SetVisibility(ESlateVisibility::Hidden);
		SetSelectedSlot(nullptr);
		purchaseList.Empty();
		sellList.Empty();
	}
}
