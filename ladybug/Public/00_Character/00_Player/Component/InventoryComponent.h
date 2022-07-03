// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "02_Item/ItemTypes.h"
#include "97_SaveGame/SaveVariable.h"

#include "InventoryComponent.generated.h"

// �κ��丮 UI������Ʈ�� ���� ��������Ʈ �Լ�
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateInven, TArray<class UItem*>, itemArray);

// �κ��丮 ������Ʈ
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
	bool IsFull();						// �κ��丮�� ���� á���� Ȯ��
	void AddItem(class UItem* item);	// �κ��丮�� ������ �߰�

	// �κ��丮���� ������ ����
	void RemoveItem(int32 index);		
	void RemoveItem(UItem* item);
	void DropItem(class UItem* item);		

	// ������ ��ġ Swap
	void SwapItem(int32 originIndex, int32 targetIndex);

	// ������ ���
	UFUNCTION(BlueprintCallable)
		void UseItem(int32 index);
public:
	// DataSetUp
	void SetInvenComponentData(FInvenComponentSave Data);

public:
	FOnUpdateInven OnUpdateInven;	// �κ��丮 ���� ������Ʈ
};
