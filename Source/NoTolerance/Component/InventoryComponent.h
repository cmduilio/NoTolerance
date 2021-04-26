// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTOLERANCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void BeginPlay() override;

	void AddItem(class UItem* Item);
	void RemoveItem(class UItem* Item);

	UPROPERTY(EditDefaultsOnly)
	int Capacity;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdate OnInventoryUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<class UItem*> Items;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UExplosiveItem* ThrowableItem;
};
