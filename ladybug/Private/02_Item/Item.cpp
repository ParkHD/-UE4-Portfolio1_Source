// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/Item.h"
#include "02_Item/ItemTypes.h"


void UItem::SetUp(FName Code, int32 Count, class UDataTable* Table)
{
	itemCode = Code;
	itemCount = Count;

	itemTable = Table;
}

bool UItem::MergeItem(UItem* target)
{
	const int32 totalCount = itemCount + target->itemCount;
	const int32 MaxCount = GetItemInfo<FItemInformation>()->item_MaxCount;

	// 아이템 개수가 남았으면 false
	if (totalCount > MaxCount)
	{
		itemCount = MaxCount;
		target->itemCount = totalCount - MaxCount;
		return false;
	}
	// 아이템 개수가 0이면 true
	else
	{
		itemCount = totalCount;
		target->itemCount = 0;
		return true;
	}
}

void UItem::UseItem(class APlayerCharacter* player)
{
	if (itemCount > 0)
	{
		itemCount--;
	}
}
void UItem::UseItem(class AWorldPlayerCharacter* player)
{
	if (itemCount > 0)
	{
		itemCount--;
	}
}