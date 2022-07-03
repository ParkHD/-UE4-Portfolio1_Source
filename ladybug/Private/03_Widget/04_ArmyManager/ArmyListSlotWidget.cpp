// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_ArmyManager/ArmyListSlotWidget.h"
#include "08_Monster/Monster.h"
#include "98_GameInstance/myGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
FReply UArmyListSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (unit != nullptr)
	{
		// 슬롯이 클릭되면 슬롯 테두리 활성화 및 유닛 정보창 업데이트
		OnClickSlot.Broadcast(this);
	}

	return FReply::Handled(); // 정상처리
}
void UArmyListSlotWidget::SetUp(class UMonster* army)
{
	// 유닛 정보로 슬롯 업데이트
	if (army != nullptr)
	{
		unit = army;
		auto monsterInfo = GetGameInstance<UmyGameInstance>()->GetMonsterInfo(army->GetTagName());
		if (monsterInfo != nullptr)
		{
			UTexture2D* texture = monsterInfo->monster_Icon;
			if (texture != nullptr)
			{
				Image_CharacterImage->SetBrushFromTexture(texture);
			}
			TextBlock_CharacterName->SetText(FText::FromString(monsterInfo->monster_Name));
			TextBlock_CharacterCount->SetText(FText::AsNumber(army->GetCount()));

			Image_SelectedFrame->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}