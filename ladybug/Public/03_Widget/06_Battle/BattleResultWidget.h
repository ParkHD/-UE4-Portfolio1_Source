// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleResultWidget.generated.h"

// ������� ����
UCLASS()
class LADYBUG_API UBattleResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_OpenLootItemManager;	// ����ǰ���� ��ư

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitBattle;			// �������� ��ư
protected:
	virtual void NativeConstruct()override;

protected:
	UFUNCTION()
		void OnOkayClickEvent();		// ����ǰ������ �̵� �Լ�
	UFUNCTION()
		void OnExitButtonEvent();		// �������� �Լ�
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
