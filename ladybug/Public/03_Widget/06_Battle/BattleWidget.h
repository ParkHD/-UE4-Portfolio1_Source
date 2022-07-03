// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UArmyListWidget* UMG_TargetArmyList;
	UPROPERTY(meta = (BindWidget))
		class UArmyListWidget* UMG_MyArmyList;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_StartBattle;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_RunAway;
protected:
	UPROPERTY()
		class AWorldPlayerCharacter* player;
	UPROPERTY()
		class AWorldMonsterCharacter* target;
public:
	void SetUp(class AWorldPlayerCharacter* Player, class AWorldMonsterCharacter* Target);
	void UpdateSlot();
protected:
	UFUNCTION()
		void OnClickStartBattleEvent();
	UFUNCTION()
		void OnClickRunAwayEvent();
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
