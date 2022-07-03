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
		// ���� �����
		slot->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UArmyListWidget::UpdateSlot(TArray<class UMonster*> armyList)
{
	// ���Ե� �ʱ�ȭ
	Init();

	for(int i = 0;i<armyList.Num();i++)
	{
		// ���� ������ �������� �ʴٸ� ���� ���� ��Ȱ��
		if (slotList.Num() > i)
		{
			// ���� SetUp
			slotList[i]->SetUp(armyList[i]);
			slotList[i]->SetVisibility(ESlateVisibility::Visible);
		}
		// ���� ������ �����ϸ� ���ο� ���� ����
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
