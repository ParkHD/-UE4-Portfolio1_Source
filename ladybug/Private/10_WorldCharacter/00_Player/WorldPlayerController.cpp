// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/00_Player/WorldPlayerController.h"

#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/01_Inventory/InventoryWidget.h"
#include "03_Widget/04_ArmyManager/ArmyManagerWidget.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "03_Widget/01_Inventory/EquipInventoryWidget.h"
#include "03_Widget/06_Battle/BattleWidget.h"
#include "03_Widget/07_Village/VillageWidget.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "10_WorldCharacter/02_StaticActor/00_Village/VillageWorldActor.h"

void AWorldPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ownerPlayer = Cast<AWorldPlayerCharacter>(aPawn);
	if (ownerPlayer != nullptr)
	{
		mainWidget = CreateWidget<UMainWidget>(this, mainWidgetClass);
		if (mainWidget != nullptr)
		{
			mainWidget->AddToViewport();
			// 함수바인딩
			// 인벤토리 업데이트
			ownerPlayer->GetInventoryComponent()->OnUpdateInven.AddUniqueDynamic(mainWidget->GetUMG_Inventory(), &UEquipInventoryWidget::UpdateInventory);
			// 장비창 업데이트
			ownerPlayer->GetEquipmentComponent()->OnUpdateEquiment.AddUniqueDynamic(mainWidget->GetUMG_Inventory(), &UEquipInventoryWidget::UpdateEquipment);
			// 스텟창 업데이트
			ownerPlayer->GetEquipmentComponent()->OnChangeEquipment.AddUniqueDynamic(mainWidget->GetUMG_Inventory(), &UEquipInventoryWidget::UpdateStatInfo);
			ownerPlayer->GetEquipmentComponent()->OnChangeEquipment.Broadcast(ownerPlayer->GetStatusComponent());
		}
	}
	SetShowMouseCursor(true);
}
void AWorldPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AWorldPlayerController::OpenInventoryWidget()
{
	auto umg_inven = mainWidget->GetUMG_Inventory();
	if (umg_inven != nullptr)
	{
		if (mainWidget->GetUMG_Inventory()->GetVisibility() == ESlateVisibility::Hidden)
		{
			mainWidget->GetUMG_Inventory()->SetVisibility(ESlateVisibility::Visible);
		}
		else if (mainWidget->GetUMG_Inventory()->GetVisibility() == ESlateVisibility::Visible)
		{
			mainWidget->GetUMG_Inventory()->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
void AWorldPlayerController::OpenArmyManagerWidget()
{
	auto umg_ArmyManager = mainWidget->GetUMG_ArmyManager();
	if (umg_ArmyManager != nullptr)
	{
		if (umg_ArmyManager->GetVisibility() == ESlateVisibility::Hidden)
		{
			umg_ArmyManager->SetVisibility(ESlateVisibility::Visible);
			umg_ArmyManager->Update(ownerPlayer->GetArmyComponent()->GetArmyList());	// 부대관리 창 업데이트
		}
		else if (umg_ArmyManager->GetVisibility() == ESlateVisibility::Visible)
		{
			umg_ArmyManager->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
void AWorldPlayerController::OpenBattleWidget(class AWorldMonsterCharacter* target)
{
	auto umg_BattleWidget = mainWidget->GetUMG_BattleWidget();
	if (umg_BattleWidget != nullptr)
	{
		if (umg_BattleWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			umg_BattleWidget->SetUp(GetPawn<AWorldPlayerCharacter>(), target);		// 전투진입 창 업데이트
			umg_BattleWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else if (umg_BattleWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			umg_BattleWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AWorldPlayerController::OpenVillageWidget(AVillageWorldActor* village)
{
	auto umg_VillageWidget = mainWidget->GetUMG_VillageWidget();
	if (umg_VillageWidget != nullptr)
	{
		if (umg_VillageWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			umg_VillageWidget->SetUp(village->GetVillageTagName());				// 마을진입 창 업데이트
			umg_VillageWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
