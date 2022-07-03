// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageWidget.generated.h"

// worldLevel에서 마을 진입창 위젯
UCLASS()
class LADYBUG_API UVillageWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
		virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageName;		// 마을 이름
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageDescription;	// 마을 설명
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_EnterVillage;				// 마을 들어가기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitVillage;				// 취소 버튼
protected:
	UPROPERTY()
		FName villageTagName;		// 마을Tag
protected:
	UFUNCTION()
		void OnClickEnterButton();	// 마을 진입 함수
	UFUNCTION()
		void OnClickExitButton();	// 취소 함수
public:
	void SetUp(FName VillageTagName);	// 위젯 Setup함수
};
