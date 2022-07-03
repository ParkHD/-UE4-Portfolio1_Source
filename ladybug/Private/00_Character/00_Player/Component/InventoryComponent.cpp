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
	// �κ��丮�� ���� �������� �ִ��� Ȯ���Ѵ�.
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] != nullptr)
		{
			if (Inventory[i]->GetItemCode() == item->GetItemCode())
			{
				// ������ �ִ� �����۰� ������ ������ ��ħ
				// ������ �������� ������ 0�� �Ǹ� return
				if (Inventory[i]->MergeItem(item))
				{
					OnUpdateInven.Broadcast(Inventory);
					return;
				}
			}
		}
	}
	// �κ��丮�� ���� �������� ���� �Ǵ�, �� ������ �ִ´�.
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
	// �κ��丮�� �ش� �ε��� ��������� �ʱ�ȭ
	Inventory.EmplaceAt(index, nullptr);
	OnUpdateInven.Broadcast(Inventory);
}

void UInventoryComponent::RemoveItem(UItem* item)
{
	// �κ��丮�� �ش� �ε����� ã�� ��������� �ʱ�ȭ
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
	// �κ��丮�� �ش� �ε����� ã�� ��������� �ʱ�ȭ
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

			// ���⿡ ��� ����â���� �Ű����Ƿ� nullptr���� �˻�
			if(Inventory[index] != nullptr)
			{
				// ī��Ʈ�� 0�Ʒ��� �κ����� �����Ѵ�.
				if (Inventory[index]->GetItemCount() <= 0)
				{
					Inventory[index] = nullptr;
				}
			}
			OnUpdateInven.Broadcast(Inventory);
		}
	}
}

