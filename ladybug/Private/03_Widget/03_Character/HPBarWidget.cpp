// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/03_Character/HPBarWidget.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "Components/ProgressBar.h"

// visible 활성화 될 때마다 호춣된다!!!!
void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
void UHPBarWidget::UpdateHPBar(class UStatusComponent* statusComp)
{
	if (statusComp != nullptr)
	{
		ProgressBar_HPBar->SetPercent(statusComp->GetHPRatio());
	}
}
void UHPBarWidget::Init()
{
	ProgressBar_HPBar->SetPercent(1.f);
}