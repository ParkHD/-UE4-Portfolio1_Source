// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UVillageNameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageName;
public:
	void SetUp(FString villageName);
};
