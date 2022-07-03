// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/Potion.h"

void UPotion::UseItem(class APlayerCharacter* player)
{
	Super::UseItem(player);
	UE_LOG(LogTemp, Log, TEXT("Use Potion"));
}