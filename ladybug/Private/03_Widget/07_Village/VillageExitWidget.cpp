// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Village/VillageExitWidget.h"

#include "99_GameMode/VillageGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UVillageExitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_ExitVillage->OnClicked.AddUniqueDynamic(this, &UVillageExitWidget::OnClickExitVillageButton);
	Button_Exit->OnClicked.AddUniqueDynamic(this, &UVillageExitWidget::OnClickExitButton);
	OnVisibilityChanged.AddUniqueDynamic(this, &UVillageExitWidget::OnVisibilityChangeEvent);
}

void UVillageExitWidget::OnClickExitVillageButton()
{
	Cast<AVillageGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OpenWorldLevel();
}

void UVillageExitWidget::OnClickExitButton()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UVillageExitWidget::OnVisibilityChangeEvent(ESlateVisibility visible)
{
	if(visible == ESlateVisibility::Hidden)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->SetShowMouseCursor(false);
	}
	else if(visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		GetOwningPlayer()->SetShowMouseCursor(true);
	}
}


