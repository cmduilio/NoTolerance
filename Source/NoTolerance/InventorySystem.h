// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTOLERANCE_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystem();

	virtual void BeginPlay() override;

	void AddItem(class UItem* Item);
	void RemoveItem(class UItem* Item);

	UPROPERTY(EditDefaultsOnly)
	int Capacity;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdate OnInventoryUpdate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<class UItem*> Items;
};
