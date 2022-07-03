// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/Item.h"
#include "Potion.generated.h"

// 포션 아이템
UCLASS()
class LADYBUG_API UPotion : public UItem
{
	GENERATED_BODY()
public:
	// 아이템 사용
	virtual void UseItem(class APlayerCharacter* player) override;
};
