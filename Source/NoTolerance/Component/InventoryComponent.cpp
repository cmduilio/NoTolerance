#include "InventoryComponent.h"

#include "../Item/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Capacity = 20;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::RemoveItem(UItem* Item)
{
	if(Item)
	{
		Item->OwningInventory = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdate.Broadcast();
	}
}

void UInventoryComponent::AddItem(UItem* Item)
{
	if (Item && Items.Num() < Capacity){
		Item->OwningInventory = this;
		Items.Add(Item);
		OnInventoryUpdate.Broadcast();
	}
}

