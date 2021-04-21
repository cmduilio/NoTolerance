#include "InventorySystem.h"

#include "../Item.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Capacity = 20;
}

void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
}

void UInventorySystem::RemoveItem(UItem* Item)
{
	if(Item)
	{
		Item->OwningInventory = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdate.Broadcast();
	}
}

void UInventorySystem::AddItem(UItem* Item)
{
	if (Item && Items.Num() < Capacity){
		Item->OwningInventory = this;
		Items.Add(Item);
		OnInventoryUpdate.Broadcast();
	}
}

