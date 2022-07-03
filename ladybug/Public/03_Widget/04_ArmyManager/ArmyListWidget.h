// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyListWidget.generated.h"

// 유닛 슬롯들을 모아놓은 리스트
UCLASS()
class LADYBUG_API UArmyListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MyName;			// "TextBlock_MyName"의 부대

	// 유닛 슬롯들을 모아놓은 리스트
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_ArmyList;
	TArray<class UArmyListSlotWidget*> slotList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ArmyListSlotWidget;
public:
	void Init();
	void UpdateSlot(TArray<class UMonster*> armyList);	// 슬롯List업데이트
	void UpdateOwner(FString myName);					// 누구의 부대인지 나타낼 Text 업데이트 -> "TextBlock_MyName"의 부대
};
