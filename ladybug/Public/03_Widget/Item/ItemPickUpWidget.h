// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UItemPickUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
public:
	void SetItemText(const FText itemName);
};
