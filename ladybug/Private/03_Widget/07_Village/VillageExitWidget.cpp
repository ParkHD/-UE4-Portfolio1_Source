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
	// WorldLevel로 이동
	Cast<AVillageGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OpenWorldLevel();
}

void UVillageExitWidget::OnClickExitButton()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UVillageExitWidget::OnVisibilityChangeEvent(ESlateVisibility visible)
{
	// 마우스 입력 및 커서 관리
	// 위젯이 꺼지면 마우스 커서를 숨기고 게임 입력 모드
	if(visible == ESlateVisibility::Hidden)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->SetShowMouseCursor(false);
	}
	// 위젯이 켜지면 마우스 커서를 보이게하고 마우스로 UI입력 모드
	else if(visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		GetOwningPlayer()->SetShowMouseCursor(true);
	}
}


