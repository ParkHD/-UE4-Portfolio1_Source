// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Battle/BattleWidget.h"
#include "03_Widget/04_ArmyManager/ArmyListWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "99_GameMode/WorldGameMode.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"

void UBattleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_StartBattle->OnClicked.AddUniqueDynamic(this, &UBattleWidget::OnClickStartBattleEvent);
	Button_RunAway->OnClicked.AddUniqueDynamic(this, &UBattleWidget::OnClickRunAwayEvent);
	OnVisibilityChanged.AddUniqueDynamic(this, &UBattleWidget::OnVisibilityChangeEvent);
}
void UBattleWidget::SetUp(class AWorldPlayerCharacter* Player, class AWorldMonsterCharacter* Target)
{
	player = Player;
	UMG_MyArmyList->UpdateOwner("Player");
	target = Target;
	UMG_TargetArmyList->UpdateOwner(target->GetWorldMonsterInfo()->monster_Name);
}
void UBattleWidget::UpdateSlot()
{
	// 부대리스트 위젯 업데이트
	if(player != nullptr)
	{
		UMG_MyArmyList->UpdateSlot(player->GetArmyComponent()->GetArmyList());
	}
	if(target != nullptr)
	{
		UMG_TargetArmyList->UpdateSlot(target->GetArmyComponent()->GetArmyList());
	}
}
void UBattleWidget::OnClickStartBattleEvent()
{
	if(player != nullptr && target != nullptr)
	{
		auto gameMode = Cast<AWorldGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gameMode != nullptr)
		{
			// 전투Level로 이동
			gameMode->OpenBattleLevel(target);
		}
	}
}
void UBattleWidget::OnClickRunAwayEvent()
{
	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
void UBattleWidget::OnVisibilityChangeEvent(ESlateVisibility visible)
{
	// 위젯이 켜지면 위젯 업데이트를 한다.
	if(visible == ESlateVisibility::Visible)
	{
		UpdateSlot();
	}
}