// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyListWidget.generated.h"

// ���� ���Ե��� ��Ƴ��� ����Ʈ
UCLASS()
class LADYBUG_API UArmyListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MyName;			// "TextBlock_MyName"�� �δ�

	// ���� ���Ե��� ��Ƴ��� ����Ʈ
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_ArmyList;
	TArray<class UArmyListSlotWidget*> slotList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ArmyListSlotWidget;
public:
	void Init();
	void UpdateSlot(TArray<class UMonster*> armyList);	// ����List������Ʈ
	void UpdateOwner(FString myName);					// ������ �δ����� ��Ÿ�� Text ������Ʈ -> "TextBlock_MyName"�� �δ�
};
