// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/StatInfoWidget.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "Components/TextBlock.h"

void UStatInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UStatInfoWidget::Update(UStatusComponent* StatComp)
{
	TextBlock_MaxHP->SetText(FText::AsNumber(StatComp->GetStat().MaxHP));
	TextBlock_MaxMP->SetText(FText::AsNumber(StatComp->GetStat().MaxMP));
	TextBlock_MaxSP->SetText(FText::AsNumber(StatComp->GetStat().MaxSP));
	TextBlock_Damage->SetText(FText::AsNumber(StatComp->GetStat().Damage));
	TextBlock_Defence->SetText(FText::AsNumber(StatComp->GetStat().Defence));
}
void UStatInfoWidget::Init()
{
	TextBlock_MaxHP->SetText(FText::FromString(""));
	TextBlock_MaxMP->SetText(FText::FromString(""));
	TextBlock_MaxSP->SetText(FText::FromString(""));
	TextBlock_Damage->SetText(FText::FromString(""));
	TextBlock_Defence->SetText(FText::FromString(""));
}
