// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_ArmyManager/ArmyInfoWidget.h"
#include "08_Monster/Monster.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/TextureRenderTarget2D.h"
#include "07_Skill/SKillBase.h"
#include "03_Widget/04_ArmyManager/ArmyListSlotWidget.h"

void UArmyInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
}
void UArmyInfoWidget::SetUp(class UArmyListSlotWidget* selectedSlot)
{
	if (selectedSlot != nullptr)
	{
		Init();

		const FMonsterInfo* monsterInfo = selectedSlot->GetUnit()->GetMonsterInfo();
		if (monsterInfo != nullptr)
		{
			UTextureRenderTarget2D* texture = monsterInfo->monster_Image;
			if (texture != nullptr)
			{
				Image_CharacterPreview->SetBrushResourceObject(monsterInfo->monster_Image);
			}
			TextBlock_UnitName->SetText(FText::FromString(monsterInfo->monster_Name));
			TextBlock_UnitDecription->SetText(FText::FromString(monsterInfo->monster_Description));

			TextBlock_MaxHP->SetText(FText::AsNumber(monsterInfo->monster_Stat.MaxHP));
			TextBlock_MaxMP->SetText(FText::AsNumber(monsterInfo->monster_Stat.MaxMP));
			TextBlock_MaxSP->SetText(FText::AsNumber(monsterInfo->monster_Stat.MaxSP));
			TextBlock_Damage->SetText(FText::AsNumber(monsterInfo->monster_Stat.Damage));
			TextBlock_Defence->SetText(FText::AsNumber(monsterInfo->monster_Stat.Defence));

			FString skillList = "";
			for (TSubclassOf<class USKillBase> skill : monsterInfo->monster_Skill)
			{
				USKillBase* skillclass = Cast<USKillBase>(skill.GetDefaultObject());
				skillList.Append(skillclass->GetSkillInfo()->skill_Name);
				skillList.Append("\n");
			}
			TextBlock_Skill->SetText(FText::FromString(skillList));
		}
	}
}

void UArmyInfoWidget::Init()
{
	Image_CharacterPreview->SetBrushResourceObject(defaultpreviewImage);

	TextBlock_UnitName->SetText(FText::FromString(""));
	TextBlock_UnitDecription->SetText(FText::FromString(""));

	TextBlock_MaxHP->SetText(FText::FromString(""));
	TextBlock_MaxMP->SetText(FText::FromString(""));
	TextBlock_MaxSP->SetText(FText::FromString(""));
	TextBlock_Damage->SetText(FText::FromString(""));
	TextBlock_Defence->SetText(FText::FromString(""));

	TextBlock_Skill->SetText(FText::FromString(""));
}