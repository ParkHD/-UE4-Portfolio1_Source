// Fill out your copyright notice in the Description page of Project Settings.
#include "00_Character/00_Player/CustomController.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "03_Widget/MainWidget.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "03_Widget/PlayerStatusWidget.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "03_Widget/BattleMainWidget.h"
#include "03_Widget/PlayerSkillWidget.h"
#include "03_Widget/06_Battle/BattleResultWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"													
#include "03_Widget/06_Battle/ItemManagerWidget.h"
#include "03_Widget/07_Village/VillageExitWidget.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "Components/Image.h"
void ACustomController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ownerPlayer = Cast<APlayerCharacter>(aPawn);
	if (ownerPlayer != nullptr)
	{
		mainWidget = CreateWidget<UBattleMainWidget>(this, mainWidgetClass);
		if (mainWidget != nullptr)
		{
			// 캐릭터 HP,SP,Stamina 변동 델리게이트
			ownerPlayer->GetStatusComponent()->OnChangeHP.AddUniqueDynamic(mainWidget->GetUMG_PlayerStatus(), &UPlayerStatusWidget::UpdateHPProgressBar);
			ownerPlayer->GetStatusComponent()->OnChangeSP.AddUniqueDynamic(mainWidget->GetUMG_PlayerStatus(), &UPlayerStatusWidget::UpdateSPProgressBar);
			ownerPlayer->GetStatusComponent()->OnChangeMP.AddUniqueDynamic(mainWidget->GetUMG_PlayerStatus(), &UPlayerStatusWidget::UpdateMPProgressBar);

			// 무기 스왑 시 위젯 변경
			ownerPlayer->GetEquipmentComponent()->OnChangeWeapon.AddUniqueDynamic(mainWidget->GetUMG_PlayerSkillInfo(), &UPlayerSkillWidget::SetUp);
			ownerPlayer->GetEquipmentComponent()->UpdateWidget();

			// 무기 스왑 시 현재 스킬 위젯 변경
			ownerPlayer->GetSkillComponent()->UpdateSkill1Able.AddUniqueDynamic(mainWidget->GetUMG_PlayerSkillInfo(), &UPlayerSkillWidget::UpdateSkill1CoolTime);
			ownerPlayer->GetSkillComponent()->UpdateSkill2Able.AddUniqueDynamic(mainWidget->GetUMG_PlayerSkillInfo(), &UPlayerSkillWidget::UpdateSkill2CoolTime);

			mainWidget->AddToViewport();
		}
	}
}

void ACustomController::TurnOnInteractKey(bool bTurn)
{
	if(mainWidget != nullptr)
	{
		mainWidget->GetInteraction()->SetVisibility(bTurn ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		auto targetNameText = mainWidget->GetInteractTarget();
		if (targetNameText != nullptr)
		{
			targetNameText->SetVisibility(bTurn ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
	}
}

void ACustomController::TurnOnAimWidget(bool bTurn)
{
	if (mainWidget != nullptr)
	{
		if(bTurn)
		{
			if(mainWidget->GetAimWidget()->GetVisibility() == ESlateVisibility::Hidden)
			{
				// AimWidget 기본 크기로 초기화
				mainWidget->GetAimWidget()->SetBrushSize(FVector2D(150, 150));
				mainWidget->GetAimWidget()->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			mainWidget->GetAimWidget()->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

FVector2D ACustomController::GetAimWidgetSize()
{
	if (mainWidget != nullptr)
	{
		return mainWidget->GetAimWidget()->Brush.GetImageSize();
	}
	return FVector2D();
}

void ACustomController::SetUpAimSize(FVector2D size2D)
{
	if (mainWidget != nullptr)
	{
		mainWidget->GetAimWidget()->Brush.SetImageSize(size2D);
	}
}

void ACustomController::SetUpTargetName(FText targetName)
{
	// 상호작용 할 타겟 이름을 나타낼 위젯 업데이트
	if(mainWidget != nullptr)
	{
		auto targetNameText = mainWidget->GetInteractTarget();
		if (targetNameText != nullptr)
		{
			targetNameText->SetText(targetName);
		}
	}
}

void ACustomController::OpenBattleResult()
{
	if(mainWidget != nullptr)
	{
		mainWidget->GetUMG_BattleResult()->SetVisibility(ESlateVisibility::Visible);
	}
}
void ACustomController::OpenItemManger(TArray<class UItem*> targetItemList)
{
	if (mainWidget != nullptr)
	{
		auto characterOwner = Cast<AWorldPlayerCharacter>(GetPawn<APlayerCharacter>()->GetWorldBaseCharacter());
		if(characterOwner != nullptr)
		{
			// 전리품List를 이용해서 위젯 업데이트
			mainWidget->GetUMG_LootItemManager()->Update(targetItemList, characterOwner->GetInventoryComponent()->GetInventory());
			mainWidget->GetUMG_LootItemManager()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ACustomController::OpenVillageExitWidget()
{
	if (mainWidget != nullptr)
	{
		mainWidget->GetUMG_VillageExitWidget()->SetVisibility(ESlateVisibility::Visible);
		
	}
}
