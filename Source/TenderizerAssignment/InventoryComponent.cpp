// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < maxSlots; i++)
	{
		InventorySlot slot;
		items.Emplace(slot);
		//UE_LOG(LogTemp, Display, TEXT("%s"), items[i].item->GetName());
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan, items[i].ToString());
	}
	// ...
	

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::TryAddItem(AItemBase* item)
{
	int index = CheckIfItemExists(item);
	if (index >= 0)
	{
		if (items[index].count < items[index].maxStackCount)
		{
			items[index].count++;
			item->PickedUp();
			return true;
		}
		else
		{
			return TryInsertIntoFirstFreeSlot(item);
		}
	}
	else
	{
		return TryInsertIntoFirstFreeSlot(item);	
	}


}

bool UInventoryComponent::TryInsertIntoFirstFreeSlot(AItemBase*& item)
{
	
	int index = FindFirstEmptySlot();
	if (index >= 0)
	{
		items.EmplaceAt(index, item);
		items[index].count = 1;
		items[index].maxStackCount = item->GetMaxStacks();
		item->PickedUp();
		return true;
	}
	
	return false;
}

void UInventoryComponent::DropItem(int slotIndex)
{
}

/// <summary>
/// Checks if the given item already exists in the inventory
/// </summary>
/// <param name="item"></param>
/// <returns>Index of item if it exists, -1 if it doesn't</returns>
int UInventoryComponent::CheckIfItemExists(AItemBase* item)
{
	for (int i = 0; i < maxSlots; i++)
	{
		if (items[i].item == item)
		{
			return i;
		}
	}

	return -1;
}

/// <summary>
/// Finds the first empty slot in the inventory
/// </summary>
/// <returns>Index of slot if it one is empty, -1 if no empty slots</returns>
int UInventoryComponent::FindFirstEmptySlot()
{
	for (int i = 0; i < maxSlots; i++)
	{
		if (items[i].item == nullptr)
		{
			return i;
		}
	}
	return -1;
}

