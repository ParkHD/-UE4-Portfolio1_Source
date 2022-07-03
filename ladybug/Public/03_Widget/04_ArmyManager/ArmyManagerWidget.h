// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyManagerWidget.generated.h"

// �Ѱ������� �δ����â ������ ����
UCLASS()
class LADYBUG_API UArmyManagerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class UArmyInfoWidget* UMG_ArmyInfo;			// ���� ����â ����

	UPROPERTY()
		class UVerticalBox* VerticalBox_ArmyList;		// ���� ����Ʈ�� ��� ���� VerticalBox
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ArmyListSlotWidget;
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button_Exit;
protected:
	UPROPERTY()
		class UArmyListSlotWidget* selectedSlot;		// ���� ���� ����Ʈ �߿� ���� ���õ� ����

public:
	void Update(TArray<class UMonster*> armyList);		// ���� ����Ʈ ������Ʈ
protected:
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
	UFUNCTION()
		void OnExitButtonClicked();
	UFUNCTION()
		void SetSelectedSlot(class UArmyListSlotWidget* listSlot);
};
