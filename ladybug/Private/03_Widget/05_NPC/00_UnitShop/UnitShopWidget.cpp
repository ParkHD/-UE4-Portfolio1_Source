// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_NPC/00_UnitShop/UnitShopWidget.h"

#include "Components/TextBlock.h"
#include "03_Widget/04_ArmyManager/ArmyListSlotWidget.h"
#include "00_Character/03_NPC/NPCCharacter.h"
#include "Components/VerticalBox.h"
#include "08_Monster/Monster.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "03_Widget/05_NPC/00_UnitShop/UnitShopInfoWidget.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "98_GameInstance/myGameInstance.h"
#include "Engine/TextureRenderTarget2D.h"

void UUnitShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Purchase->OnClicked.AddUniqueDynamic(this, &UUnitShopWidget::OnClickPurchase);
	Button_Cancel->OnClicked.AddUniqueDynamic(this, &UUnitShopWidget::OnClickCancel);

	Button_ExitButton->OnClicked.AddUniqueDynamic(this, &UUnitShopWidget::OnClickExit);
	Button_ShowInfo->OnClicked.AddUniqueDynamic(this, &UUnitShopWidget::OnClickInfo);
	OnVisibilityChanged.AddUniqueDynamic(this, &UUnitShopWidget::OnVisibilityChangedEvent);
}

void UUnitShopWidget::Init()
{
	VerticalBox_ShopList->ClearChildren();
	VerticalBox_MyUnitList->ClearChildren();

	selectedSlot = nullptr;
	UMG_UnitInfo->SetVisibility(ESlateVisibility::Hidden);
	purchaseList.Empty();

	Image_CharacterPreview->SetBrushResourceObject(emptyPreviewImage);
	TextBlock_UnitName->SetText(FText::FromString(""));
}

void UUnitShopWidget::Update(TArray<class UMonster*> npcShopList, TArray<class UMonster*> myList)
{
	Init();

	if (UMG_ListSlotWidget != nullptr)
	{
		for (class UMonster* shopUnit : npcShopList)
		{
			if(shopUnit != nullptr)
			{
				UArmyListSlotWidget* armySlot = CreateWidget<UArmyListSlotWidget>(GetOwningPlayer(), UMG_ListSlotWidget);

				armySlot->OnClickSlot.AddUniqueDynamic(UMG_UnitInfo, &UUnitShopInfoWidget::SetUp);
				armySlot->OnClickSlot.AddUniqueDynamic(this, &UUnitShopWidget::SetSelectedSlot);

				armySlot->SetUp(shopUnit);
				VerticalBox_ShopList->AddChild(armySlot);
			}
		}
		for (UMonster* myUnit : myList)
		{
			if(myUnit != nullptr)
			{
				UArmyListSlotWidget* armySlot = CreateWidget<UArmyListSlotWidget>(GetOwningPlayer(), UMG_ListSlotWidget);

				armySlot->SetUp(myUnit);
				VerticalBox_MyUnitList->AddChild(armySlot);
			}
		}
	}
}
void UUnitShopWidget::SetSelectedSlot(class UArmyListSlotWidget* listSlot)
{
	if (selectedSlot != nullptr)
	{
		selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Hidden);
	}
	selectedSlot = listSlot;
	SetPreviewImage();
	selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Visible);
}
void UUnitShopWidget::SetPreviewImage()
{
	if (selectedSlot != nullptr)
	{
		auto monsterInfo = selectedSlot->GetUnit()->GetMonsterInfo();
		if(monsterInfo != nullptr)
		{
			TextBlock_UnitName->SetText((FText::FromString(monsterInfo->monster_Name)));
			UTextureRenderTarget2D* texture = monsterInfo->monster_Image;
			if (texture != nullptr)
			{
				Image_CharacterPreview->SetBrushResourceObject(texture);
			}
		}
	}
}

void UUnitShopWidget::OnClickExit()
{
	if(npcOwner)
	{
		for(UMonster* unit : purchaseList)
		{
			npcOwner->GetCaller()->GetWorldBaseCharacter()->GetArmyComponent()->AddArmy(unit);
			npcOwner->GetShopList().Remove(unit);
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UUnitShopWidget::OnClickPurchase()
{
	if(selectedSlot != nullptr)
	{
		if(!purchaseList.Contains(selectedSlot->GetUnit()))
		{
			purchaseList.Emplace(selectedSlot->GetUnit());
			VerticalBox_MyUnitList->AddChildToVerticalBox(selectedSlot);
		}
	}
}
void UUnitShopWidget::OnClickCancel()
{
	if(selectedSlot != nullptr)
	{
		VerticalBox_ShopList->AddChildToVerticalBox(selectedSlot);
		purchaseList.Remove(selectedSlot->GetUnit());
	}
}
void UUnitShopWidget::OnClickInfo()
{
	if(UMG_UnitInfo->GetVisibility() == ESlateVisibility::Hidden)
	{
		if (selectedSlot != nullptr)
		{
			UMG_UnitInfo->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if(UMG_UnitInfo->GetVisibility() == ESlateVisibility::Visible)
	{
		UMG_UnitInfo->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UUnitShopWidget::OnVisibilityChangedEvent(ESlateVisibility visible)
{
	if (visible == ESlateVisibility::Visible)
	{
		//Update(shopList, npcOwner->GetCaller()->GetWorldBaseCharacter()->GetArmyComponent()->GetArmyList());
	}
	else if(visible == ESlateVisibility::Hidden)
	{
		selectedSlot = nullptr;
		UMG_UnitInfo->SetVisibility(ESlateVisibility::Hidden);
		purchaseList.Empty();
	}
}