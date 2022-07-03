// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyListSlotWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickSlot, class UArmyListSlotWidget*, slot);

UCLASS()
class LADYBUG_API UArmyListSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
protected:
	UPROPERTY()
		class UImage* Image_CharacterImage;
	UPROPERTY()
		class UTextBlock* TextBlock_CharacterName;
	UPROPERTY()
		class UTextBlock* TextBlock_CharacterCount;
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_SelectedFrame; 
public:
	class UImage* GetSelectedFrame() { return Image_SelectedFrame; }
protected:
	UPROPERTY()
		class UMonster* unit;
public:
	class UMonster* GetUnit() { return unit; }
	void SetUp(class UMonster* army);
public:
	FOnClickSlot OnClickSlot;
};
