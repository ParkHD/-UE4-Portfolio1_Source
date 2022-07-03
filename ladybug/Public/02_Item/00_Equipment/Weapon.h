// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/00_Equipment/Equipment.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UWeapon : public UEquipment
{
	GENERATED_BODY()
	
public:
	virtual void UseItem(class APlayerCharacter* player) override;
	virtual void UseItem(class AWorldPlayerCharacter* player) override;

};
