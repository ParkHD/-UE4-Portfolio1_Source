// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "02_Item/ItemTypes.h"
#include "97_SaveGame/SaveVariable.h"

#include "InventoryComponent.generated.h"

// 인벤토리 UI업데이트를 위한 델리게이트 함수
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateInven, TArray<class UItem*>, itemArray);

// 인벤토리 컴포넌트
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LADYBUG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(VisibleAnywhere)
		TArray<class UItem*> Inventory;
public:
	const int32 Inventory_Size = 35;
	const TArray<class UItem*> GetInventory() { return Inventory; }

public:
	bool IsFull();						// 인벤토리가 가득 찼는지 확인
	void AddItem(class UItem* item);	// 인벤토리에 아이템 추가

	// 인벤토리에서 아이템 삭제
	void RemoveItem(int32 index);		
	void RemoveItem(UItem* item);
	void DropItem(class UItem* item);		

	// 아이템 위치 Swap
	void SwapItem(int32 originIndex, int32 targetIndex);

	// 아이템 사용
	UFUNCTION(BlueprintCallable)
		void UseItem(int32 index);
public:
	// DataSetUp
	void SetInvenComponentData(FInvenComponentSave Data);

public:
	FOnUpdateInven OnUpdateInven;	// 인벤토리 위젯 업데이트
};
