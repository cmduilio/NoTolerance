// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class NOTOLERANCE_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ActionText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* PickupMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText Description;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;
	
	virtual void Use(class AHero* Hero) PURE_VIRTUAL(UItem,);

	bool Equals(FText Item);
	
};
