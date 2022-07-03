// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/Item.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UPotion : public UItem
{
	GENERATED_BODY()
public:
	virtual void UseItem(class APlayerCharacter* player) override;

};
