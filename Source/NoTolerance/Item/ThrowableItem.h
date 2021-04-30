// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ThrowableItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class NOTOLERANCE_API UThrowableItem : public UItem
{
	GENERATED_BODY()
	
public:
	virtual void Use(class AActor* Container ) PURE_VIRTUAL(UThrowableItem,);
	virtual void Use(class AHero* Hero ) PURE_VIRTUAL(UItem,);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
};
