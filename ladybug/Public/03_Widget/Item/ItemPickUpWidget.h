// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickUpWidget.generated.h"

// 현재는 사용안함
// 아이템 근처에 가면 나올 위젯
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
