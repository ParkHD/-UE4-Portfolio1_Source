// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_ArmyManager/ArmyManagerWidget.h"
#include "Components/VerticalBox.h"
#include "08_Monster/Monster.h"
#include "03_Widget/04_ArmyManager/ArmyListSlotWidget.h"
#include "03_Widget/04_ArmyManager/ArmyInfoWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UArmyManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//OnVisibilityChanged.AddUniqueDynamic(this, &UArmyManagerWidget::OnVisibilityChangedEvent);
	Button_Exit->OnClicked.AddUniqueDynamic(this, &UArmyManagerWidget::OnExitButtonClicked);
}

void UArmyManagerWidget::Update(TArray<class UMonster*> armyList)
{
	// ���Ե��� �ʱ�ȭ
	VerticalBox_ArmyList->ClearChildren();

	// ArmyList�� �°� ������ �ٽ� ������ְ� SetUp�Ͽ� VerticalBox�� �־��ش�.
	for (UMonster* army : armyList)
	{
		if (army != nullptr)
		{
			UArmyListSlotWidget* armySlot = CreateWidget<UArmyListSlotWidget>(GetOwningPlayer(), UMG_ArmyListSlotWidget);

			// ���� Ŭ�� �� ����â ������Ʈ �� ���� �׵θ� ǥ���� ��������Ʈ �Լ��� ���ε�
			armySlot->OnClickSlot.AddUniqueDynamic(UMG_ArmyInfo, &UArmyInfoWidget::SetUp);
			armySlot->OnClickSlot.AddUniqueDynamic(this, &UArmyManagerWidget::SetSelectedSlot);

			armySlot->SetUp(army);

			VerticalBox_ArmyList->AddChild(armySlot);
		}
	}
}
void UArmyManagerWidget::OnVisibilityChangedEvent(ESlateVisibility visible)
{
	// �δ����â�� ������ UI �Է¹ޱ� ���
	if (visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = true;
		// �ʱ�ȭ
		UMG_ArmyInfo->Init();
		selectedSlot = nullptr;
	}
	else if (visible == ESlateVisibility::Hidden)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = false;
	}
}
void UArmyManagerWidget::OnExitButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
void UArmyManagerWidget::SetSelectedSlot(class UArmyListSlotWidget* listSlot)
{
	// ���� selectedSlot�� �׵θ� ǥ�ø� ���ְ� ���ο� selectedSlot�� �׵θ� ǥ�ø� ���ش�.
	if (selectedSlot != nullptr)
	{
		selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Hidden);
	}
	selectedSlot = listSlot;
	selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Visible);
}