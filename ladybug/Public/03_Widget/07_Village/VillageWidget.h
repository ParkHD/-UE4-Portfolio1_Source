// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UVillageWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
		virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageName;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageDescription;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_EnterVillage;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitVillage;
protected:
	UPROPERTY()
		FName villageTagName;
protected:
	UFUNCTION()
		void OnClickEnterButton();
	UFUNCTION()
		void OnClickExitButton();
public:
	void SetUp(FName VillageTagName);
};
