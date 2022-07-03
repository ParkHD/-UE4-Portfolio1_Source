// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UBattleResultWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct()override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_OpenLootItemManager;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitBattle;
protected:
	UFUNCTION()
		void OnOkayClickEvent();
	UFUNCTION()
		void OnExitButtonEvent();
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
