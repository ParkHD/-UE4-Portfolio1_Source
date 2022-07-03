// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UInventoryPannelWidget* UMG_InventoryPannel;

public:
	class UInventoryPannelWidget* GetUMG_InventoryPannel() { return UMG_InventoryPannel; }
};
