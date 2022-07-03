// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Village/VillageNameWidget.h"
#include "Components/TextBlock.h"

void UVillageNameWidget::SetUp(FString villageName)
{
	TextBlock_VillageName->SetText(FText::FromString(villageName));
}
