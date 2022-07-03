// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LADYBUG_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem(){}
	~UItem(){ UE_LOG(LogTemp, Error, TEXT("desitem")); }
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UDataTable* itemTable;

	UPROPERTY(EditAnywhere)
		FName itemCode;
	UPROPERTY(EditAnywhere)
		int32 itemCount;
public:
	const FName& GetItemCode() { return itemCode; }
	const int32& GetItemCount() { return itemCount; }
	
public:
	template<typename T>
	const T* GetItemInfo();

	void SetUp(FName Code, int32 Count, class UDataTable* Table);
	bool MergeItem(UItem* target);

	virtual void UseItem(class APlayerCharacter* player);
	virtual void UseItem(class AWorldPlayerCharacter* player);

	virtual void ItemStatSetUp(){}
};

template<typename T>
inline const T* UItem::GetItemInfo()
{
	if (itemTable != nullptr)
	{
		return itemTable->FindRow<T>(itemCode, "");
	}
	return nullptr;
}

