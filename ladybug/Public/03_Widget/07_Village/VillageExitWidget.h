// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageExitWidget.generated.h"

// ���������� ����
UCLASS()
class LADYBUG_API UVillageExitWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitVillage;	// ���� ������ ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Exit;			// ��� ��ư

protected:
	UFUNCTION()
		void OnClickExitVillageButton();		// ���� ������ �Լ�
	UFUNCTION()
		void OnClickExitButton();				// ��� �Լ�
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
