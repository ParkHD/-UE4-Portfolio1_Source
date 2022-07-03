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
		OnClickSlot.Broadcast(this);
	}

	return FReply::Handled(); // 정상처리
}
void UArmyListSlotWidget::SetUp(class UMonster* army)
{
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