// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageWidget.generated.h"

// worldLevel���� ���� ����â ����
UCLASS()
class LADYBUG_API UVillageWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
		virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageName;		// ���� �̸�
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageDescription;	// ���� ����
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_EnterVillage;				// ���� ���� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitVillage;				// ��� ��ư
protected:
	UPROPERTY()
		FName villageTagName;		// ����Tag
protected:
	UFUNCTION()
		void OnClickEnterButton();	// ���� ���� �Լ�
	UFUNCTION()
		void OnClickExitButton();	// ��� �Լ�
public:
	void SetUp(FName VillageTagName);	// ���� Setup�Լ�
};
