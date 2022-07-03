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
	// 위젯 초기화
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
		// 파는 물품 목록을 가져와서 슬롯을 만들어주고 VerticalBox에 넣어준다.
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
		// 나의 물품 목록을 가져와서 슬롯을 만들어주고 VerticalBox에 넣어준다.
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
	// 기존에 선택되어 있는 슬롯의 테두르표시는 꺼주고 새롭게 선택된 슬롯의 테두리표시를 켜준다.
	if (selectedSlot != nullptr)
	{
		selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Hidden);
	}
	selectedSlot = listSlot;
	
	SetPreviewImage();			// 선택된 슬롯에 맞게 preview이미지 변경
	selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Visible);
}
void UUnitShopWidget::SetPreviewImage()
{
	if (selectedSlot != nullptr)
	{
		// 유닛의 정보를 가져와서 previewImage를 변경해준다.
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
	// 나가기 버튼을 누르면 구매리스트를 내 부대에 추가하고 NPC의 상점List에서는 삭제한다.
	if(npcOwner)
	{
		for(UMonster* unit : purchaseList)
		{
			npcOwner->GetCaller()->GetWorldBaseCharacter()->GetArmyComponent()->AddArmy(unit);
			npcOwner->GetShopList().Remove(unit);
		}
	}
	// 위젯을 끈다.
	SetVisibility(ESlateVisibility::Hidden);
}

void UUnitShopWidget::OnClickPurchase()
{
	if(selectedSlot != nullptr)
	{
		if(!purchaseList.Contains(selectedSlot->GetUnit()))
		{
			// 구매목록에 추가
			purchaseList.Emplace(selectedSlot->GetUnit());
			// 슬롯을 내 목록으로 이동
			VerticalBox_MyUnitList->AddChildToVerticalBox(selectedSlot);
		}
	}
}
void UUnitShopWidget::OnClickCancel()
{
	if(selectedSlot != nullptr)
	{
		// 구매목록에서 제거 하고 슬롯을 내 목록에서 상점 목록으로 이동
		VerticalBox_ShopList->AddChildToVerticalBox(selectedSlot);
		purchaseList.Remove(selectedSlot->GetUnit());
	}
}
void UUnitShopWidget::OnClickInfo()
{
	// 정보창이 닫혀있으면 열고 열려있으면 닫는다.
	if(UMG_UnitInfo->GetVisibility() == ESlateVisibility::Hidden)
	{
		// 현재 선택된 슬롯이 있으면 정보창을 연다.
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