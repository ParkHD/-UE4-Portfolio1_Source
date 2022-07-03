// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

// 아이템class
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
		FName itemCode;			// Item구분지을 고유 코드
	UPROPERTY(EditAnywhere)
		int32 itemCount;		// 아이템 개수
public:
	const FName& GetItemCode() { return itemCode; }
	const int32& GetItemCount() { return itemCount; }
	
public:
	// 아이템 정보 가져오기
	template<typename T>
	const T* GetItemInfo();	

	void SetUp(FName Code, int32 Count, class UDataTable* Table);	// 아이템 설정
	bool MergeItem(UItem* target);									// 아이템 개수 합치기

	virtual void UseItem(class APlayerCharacter* player);			// 아이템 사용
	virtual void UseItem(class AWorldPlayerCharacter* player);

	virtual void ItemStatSetUp(){}									// 아이템 능력치 설정
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

