// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "02_Item/Item.h"
#include "02_Item/Potion.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"




// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Inventory.Init(nullptr, Inventory_Size);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SetInvenComponentData(FInvenComponentSave Data)
{
	Inventory = Data.ItemList;
	OnUpdateInven.Broadcast(Inventory);
}

bool UInventoryComponent::IsFull()
{
	for(auto item : Inventory)
	{
		if(item == nullptr)
			return false;
	}
	return true;
}

void UInventoryComponent::AddItem(UItem* item)
{
	// 인벤토리에 같은 아이템이 있는지 확인한다.
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] != nullptr)
		{
			if (Inventory[i]->GetItemCode() == item->GetItemCode())
			{
				// 기존에 있던 아이템과 습득한 아이템 합침
				// 습득한 아이템의 개수가 0이 되면 return
				if (Inventory[i]->MergeItem(item))
				{
					OnUpdateInven.Broadcast(Inventory);
					return;
				}
			}
		}
	}
	// 인벤토리에 같은 아이템이 없다 판단, 빈 공간에 넣는다.
	for (int i = 0; i < Inventory_Size; i++)
	{
		if (Inventory[i] == nullptr)
		{
			Inventory[i] = item;
			OnUpdateInven.Broadcast(Inventory);
			break;															
		}
	}
}

void UInventoryComponent::RemoveItem(int32 index)
{
	// 인벤토리의 해당 인덱스 빈공간으로 초기화
	Inventory.EmplaceAt(index, nullptr);
	OnUpdateInven.Broadcast(Inventory);
}

void UInventoryComponent::RemoveItem(UItem* item)
{
	// 인벤토리의 해당 인덱스를 찾고 빈공간으로 초기화
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] == item)
		{
			Inventory[i] = nullptr;
			break;
		}
	}
}

void UInventoryComponent::DropItem(class UItem* item)
{
	// 인벤토리의 해당 인덱스를 찾고 빈공간으로 초기화
	for(int i = 0; i<Inventory.Num();i++)
	{
		if(Inventory[i] == item)
		{
			Inventory[i] = nullptr;
			break;
		}
	}
}
void UInventoryComponent::SwapItem(int32 originIndex, int32 targetIndex)
{
	Inventory.Swap(originIndex, targetIndex);
	OnUpdateInven.Broadcast(Inventory);
}


void UInventoryComponent::UseItem(int32 index)
{
	if (Inventory[index] != nullptr)
	{
		if (Inventory[index]->GetItemCount() > 0)
		{
			Inventory[index]->UseItem(GetOwner<AWorldPlayerCharacter>());

			// 무기에 경우 무기창으로 옮겨지므로 nullptr인지 검사
			if(Inventory[index] != nullptr)
			{
				// 카운트가 0아래면 인벤에서 삭제한다.
				if (Inventory[index]->GetItemCount() <= 0)
				{
					Inventory[index] = nullptr;
				}
			}
			OnUpdateInven.Broadcast(Inventory);
		}
	}
}

