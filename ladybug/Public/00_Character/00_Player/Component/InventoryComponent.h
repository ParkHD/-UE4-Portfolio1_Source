// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "02_Item/ItemTypes.h"
#include "97_SaveGame/SaveVariable.h"

#include "InventoryComponent.generated.h"

// 인벤토리 UI업데이트를 위한 델리게이트 함수
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateInven, TArray<class UItem*>, itemArray);

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
public:
	const TArray<class UItem*> GetInventory() { return Inventory; }

public:
	void SetInvenComponentData(FInvenComponentSave Data);

	bool IsFull();
	void AddItem(class UItem* item);
	void RemoveItem(int32 index);
	void RemoveItem(class UItem* item);


	void DropItem(class UItem* item);

	void SwapItem(int32 originIndex, int32 targetIndex);

	UFUNCTION(BlueprintCallable)
		void UseItem(int32 index);


public:
	FOnUpdateInven OnUpdateInven;
};
