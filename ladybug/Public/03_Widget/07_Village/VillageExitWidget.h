// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageExitWidget.generated.h"

// 마을나가기 위젯
UCLASS()
class LADYBUG_API UVillageExitWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitVillage;	// 마을 나가기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Exit;			// 취소 버튼

protected:
	UFUNCTION()
		void OnClickExitVillageButton();		// 마을 나가기 함수
	UFUNCTION()
		void OnClickExitButton();				// 취소 함수
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
