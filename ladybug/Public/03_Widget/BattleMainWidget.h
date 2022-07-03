// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UBattleMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UBattleResultWidget* UMG_BattleResult;
	UPROPERTY(meta = (BindWidget))
		class UPlayerStatusWidget* UMG_PlayerStatus;
	UPROPERTY(meta = (BindWidget))
		class UItemManagerWidget* UMG_LootItemManager;
	UPROPERTY(meta = (BindWidget))
		class UVillageExitWidget* UMG_VillageExitWidget;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextBlock_InteractTarget;
	UPROPERTY(Meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_Interaction;
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_Aim;
	UPROPERTY(Meta = (BindWidget))
		class UPlayerSkillWidget* UMG_PlayerSkillInfo;
public:
	class UBattleResultWidget* GetUMG_BattleResult() { return UMG_BattleResult; }
	class UPlayerStatusWidget* GetUMG_PlayerStatus() { return UMG_PlayerStatus; }
	class UItemManagerWidget* GetUMG_LootItemManager() { return UMG_LootItemManager; }
	class UVillageExitWidget* GetUMG_VillageExitWidget() { return UMG_VillageExitWidget; }
	class UTextBlock* GetInteractTarget() { return TextBlock_InteractTarget; }
	class UHorizontalBox* GetInteraction() { return HorizontalBox_Interaction; }
	class UImage* GetAimWidget() { return Image_Aim; }

	class UPlayerSkillWidget* GetUMG_PlayerSkillInfo() { return UMG_PlayerSkillInfo; }
};
