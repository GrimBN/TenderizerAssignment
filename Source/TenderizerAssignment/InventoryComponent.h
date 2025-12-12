// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemBase.h"
#include "InventoryComponent.generated.h"

struct InventorySlot
{
	AItemBase* item = nullptr;
	int count;
	int maxStackCount;

	FString ToString()
	{
		if (item != nullptr)
		{
			return item->GetName();
		}
		return "Slot is Empty";
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TENDERIZERASSIGNMENT_API UInventoryComponent : public UActorComponent
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

	UFUNCTION()
	bool TryAddItem(AItemBase* item);

	bool TryInsertIntoFirstFreeSlot(AItemBase*& item);

	UFUNCTION()
	void DropItem(int slotIndex);

	int CheckIfItemExists(AItemBase* item);

	int FindFirstEmptySlot();

	

private:

	UPROPERTY(EditAnywhere)
	int maxSlots;

	TArray<InventorySlot> items;



		
};
