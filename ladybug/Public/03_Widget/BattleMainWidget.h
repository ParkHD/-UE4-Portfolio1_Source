// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleMainWidget.generated.h"

// BattleCharacter모드에서 사용하는 MainWidget
UCLASS()
class LADYBUG_API UBattleMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UBattleResultWidget* UMG_BattleResult;		// 전투결과 위젯
	UPROPERTY(meta = (BindWidget))
		class UPlayerStatusWidget* UMG_PlayerStatus;		// 플레이어 상태창
	UPROPERTY(meta = (BindWidget))
		class UItemManagerWidget* UMG_LootItemManager;		// 전리품 관리창
	UPROPERTY(meta = (BindWidget))
		class UVillageExitWidget* UMG_VillageExitWidget;	// 마을 나가기 위젯
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextBlock_InteractTarget;			// 상호작용 위젯
	UPROPERTY(Meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_Interaction;	// 상호작용 위젯
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_Aim;							// Aim위젯
	UPROPERTY(Meta = (BindWidget))
		class UPlayerSkillWidget* UMG_PlayerSkillInfo;		// 스킬 정보 위젯
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
