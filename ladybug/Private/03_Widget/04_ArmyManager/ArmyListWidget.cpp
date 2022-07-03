// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_ArmyManager/ArmyListWidget.h"
#include "Components/VerticalBox.h"
#include "08_Monster/Monster.h"
#include "03_Widget/04_ArmyManager/ArmyListSlotWidget.h"
#include "Components/TextBlock.h"

void UArmyListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	VerticalBox_ArmyList->ClearChildren();

	Init();
}
void UArmyListWidget::Init()
{
	for(UArmyListSlotWidget* slot : slotList)
	{
		// 슬롯 숨기기
		slot->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UArmyListWidget::UpdateSlot(TArray<class UMonster*> armyList)
{
	// 슬롯들 초기화
	Init();

	for(int i = 0;i<armyList.Num();i++)
	{
		// 슬롯 개수가 부족하지 않다면 기존 슬롯 재활용
		if (slotList.Num() > i)
		{
			// 슬롯 SetUp
			slotList[i]->SetUp(armyList[i]);
			slotList[i]->SetVisibility(ESlateVisibility::Visible);
		}
		// 슬롯 개수가 부족하면 새로운 슬롯 생성
		else
		{
			UArmyListSlotWidget* armySlot = CreateWidget<UArmyListSlotWidget>(GetOwningPlayer(), UMG_ArmyListSlotWidget);
			slotList.Emplace(armySlot);
			armySlot->SetUp(armyList[i]);
			VerticalBox_ArmyList->AddChildToVerticalBox(armySlot);
			armySlot->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UArmyListWidget::UpdateOwner(FString myName)
{
	TextBlock_MyName->SetText(FText::FromString(myName.Append("'s Army")));
}
