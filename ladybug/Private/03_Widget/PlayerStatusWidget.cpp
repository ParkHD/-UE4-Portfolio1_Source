// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/PlayerStatusWidget.h"
#include "Components/ProgressBar.h"
#include "00_Character/00_Player/Component/StatusComponent.h"

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
}
void UPlayerStatusWidget::Init()
{
	ProgressBar_HP->SetPercent(1.f);
	ProgressBar_SP->SetPercent(1.f);
	ProgressBar_MP->SetPercent(0.f);
}
void UPlayerStatusWidget::UpdateHPProgressBar(class UStatusComponent* statusComp)
{
	ProgressBar_HP->SetPercent(statusComp->GetHPRatio());
}
void UPlayerStatusWidget::UpdateSPProgressBar(class UStatusComponent* statusComp)
{
	ProgressBar_SP->SetPercent(statusComp->GetSPRatio());
}

void UPlayerStatusWidget::UpdateMPProgressBar(UStatusComponent* statusComp)
{
	ProgressBar_MP->SetPercent(statusComp->GetMPRatio());
}
