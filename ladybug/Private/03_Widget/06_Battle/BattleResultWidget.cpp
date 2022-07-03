// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Battle/BattleResultWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/CustomController.h"
#include "98_GameInstance/myGameInstance.h"
#include "99_GameMode/00_GameState/BattleGameState.h"
#include "99_GameMode/BattleGameMode.h"

void UBattleResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnVisibilityChanged.AddUniqueDynamic(this, &UBattleResultWidget::OnVisibilityChangeEvent);
	Button_OpenLootItemManager->OnClicked.AddUniqueDynamic(this, &UBattleResultWidget::OnOkayClickEvent);
	Button_ExitBattle->OnClicked.AddUniqueDynamic(this, &UBattleResultWidget::OnExitButtonEvent);
}
void UBattleResultWidget::OnOkayClickEvent()
{
	auto controller = GetOwningPlayer<ACustomController>();
	if(controller != nullptr)
	{
		auto gameInstance = GetGameInstance<UmyGameInstance>();
		if(gameInstance != nullptr)
		{
			// 傈府前包府 芒阑 挪促.
			controller->OpenItemManger(gameInstance->lootItemList);
		}
	}
}

void UBattleResultWidget::OnExitButtonEvent()
{
	Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OpenWorldLevel();
}

void UBattleResultWidget::OnVisibilityChangeEvent(ESlateVisibility visible)
{
	// 付快胶 目辑 包府
	if(visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = true;
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
	}
	else if(visible == ESlateVisibility::Hidden)
	{
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = false;
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	}
}
