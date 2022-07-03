// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/PlayerSkillWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "07_Skill/SKillBase.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UPlayerSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UPlayerSkillWidget::SetUp(FWeaponInformation weaponInfo)
{
	Init();

	for(int i = 0;i<weaponInfo.Weapon_Skills.Num();i++)
	{
		auto skillInfo = weaponInfo.Weapon_Skills[i].GetDefaultObject()->GetSkillInfo();
		if (skillInfo != nullptr)
		{
			auto owner = GetOwningPlayerPawn<APlayerCharacter>();
			if(owner != nullptr)
			{
				if (i == 0)
				{
					Image_Skill1_Image->SetBrushFromTexture(skillInfo->skill_Image);
					Image_Skill1_Image->SetVisibility(ESlateVisibility::Visible);
					

				}
				else if (i == 1)
				{
					Image_Skill2_Image->SetBrushFromTexture(skillInfo->skill_Image);
					Image_Skill2_Image->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}

	Image_WeaponImage->SetVisibility(ESlateVisibility::Visible);
	switch(weaponInfo.WeaponType)
	{
	case EWeaponType::ONEHAND:
		Image_WeaponImage->SetBrushFromTexture(OneHandSwordImage);
		break;
	case EWeaponType::BOW:
		Image_WeaponImage->SetBrushFromTexture(ArrowImage);
		break;
	default:
		Image_WeaponImage->SetBrushFromTexture(nullptr);
		Image_WeaponImage->SetVisibility(ESlateVisibility::Hidden);
		break;
	}

}

void UPlayerSkillWidget::UpdateSkill1CoolTime(bool skillAble)
{
	if(skillAble)
	{
		Image_LockSkill1->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Image_LockSkill1->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerSkillWidget::UpdateSkill2CoolTime(bool skillAble)
{
	if (skillAble)
	{
		Image_LockSkill2->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Image_LockSkill2->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerSkillWidget::Init()
{
	Image_Skill1_Image->SetBrushFromTexture(nullptr);
	Image_Skill1_Image->SetVisibility(ESlateVisibility::Hidden);

	Image_Skill2_Image->SetBrushFromTexture(nullptr);
	Image_Skill2_Image->SetVisibility(ESlateVisibility::Hidden);

	Image_WeaponImage->SetBrushFromTexture(nullptr);
	Image_WeaponImage->SetVisibility(ESlateVisibility::Hidden);
}
