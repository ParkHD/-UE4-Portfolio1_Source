// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Village/VillageWidget.h"

#include "98_GameInstance/myGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "99_GameMode/WorldGameMode.h"
#include "Components/TextBlock.h"

void UVillageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_EnterVillage->OnClicked.AddUniqueDynamic(this, &UVillageWidget::UVillageWidget::OnClickEnterButton);
	Button_ExitVillage->OnClicked.AddUniqueDynamic(this, &UVillageWidget::UVillageWidget::OnClickExitButton);
}

void UVillageWidget::OnClickEnterButton()
{
	// VillageLevel�� ����
	if(!villageTagName.IsNone())
	{
		Cast<AWorldGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OpenVillageLevel(villageTagName);
	}
}

void UVillageWidget::OnClickExitButton()
{
	SetVisibility(ESlateVisibility::Hidden);
	// �ߴܵ� ���� �ٽ� �����ϱ�
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UVillageWidget::SetUp(FName VillageTagName)
{
	// ���� ������Ʈ
	villageTagName = VillageTagName;
	// �����ν��Ͻ����� ���� ��������
	auto info = GetGameInstance<UmyGameInstance>()->GetVillageInfo(villageTagName);
	if(info != nullptr)
	{
		TextBlock_VillageName->SetText(FText::FromString(info->village_Name));
		TextBlock_VillageDescription->SetText(FText::FromString(info->village_Description));
	}
}
