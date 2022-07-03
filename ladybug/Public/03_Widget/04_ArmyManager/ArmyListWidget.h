// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyListWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UArmyListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MyName;
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_ArmyList;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ArmyListSlotWidget;

	TArray<class UArmyListSlotWidget*> slotList;
public:
	void Init();
	void UpdateSlot(TArray<class UMonster*> armyList);
	void UpdateOwner(FString myName);
};
