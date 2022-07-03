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
	// 슬롯들을 초기화
	VerticalBox_ArmyList->ClearChildren();

	// ArmyList에 맞게 슬롯을 다시 만들어주고 SetUp하여 VerticalBox에 넣어준다.
	for (UMonster* army : armyList)
	{
		if (army != nullptr)
		{
			UArmyListSlotWidget* armySlot = CreateWidget<UArmyListSlotWidget>(GetOwningPlayer(), UMG_ArmyListSlotWidget);

			// 슬롯 클릭 시 정보창 업데이트 및 슬롯 테두리 표시할 델리게이트 함수에 바인딩
			armySlot->OnClickSlot.AddUniqueDynamic(UMG_ArmyInfo, &UArmyInfoWidget::SetUp);
			armySlot->OnClickSlot.AddUniqueDynamic(this, &UArmyManagerWidget::SetSelectedSlot);

			armySlot->SetUp(army);

			VerticalBox_ArmyList->AddChild(armySlot);
		}
	}
}
void UArmyManagerWidget::OnVisibilityChangedEvent(ESlateVisibility visible)
{
	// 부대관리창이 켜지면 UI 입력받기 모드
	if (visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = true;
		// 초기화
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
	// 원래 selectedSlot의 테두리 표시를 꺼주고 새로운 selectedSlot의 테두리 표시를 켜준다.
	if (selectedSlot != nullptr)
	{
		selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Hidden);
	}
	selectedSlot = listSlot;
	selectedSlot->GetSelectedFrame()->SetVisibility(ESlateVisibility::Visible);
}