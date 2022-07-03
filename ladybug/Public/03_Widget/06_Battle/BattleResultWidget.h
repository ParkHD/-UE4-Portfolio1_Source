// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleResultWidget.generated.h"

// 전투결과 위젯
UCLASS()
class LADYBUG_API UBattleResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_OpenLootItemManager;	// 전리품관리 버튼

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitBattle;			// 전투종료 버튼
protected:
	virtual void NativeConstruct()override;

protected:
	UFUNCTION()
		void OnOkayClickEvent();		// 전리품관리로 이동 함수
	UFUNCTION()
		void OnExitButtonEvent();		// 전투종료 함수
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
