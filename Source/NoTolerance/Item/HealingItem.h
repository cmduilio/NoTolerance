// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API UHealingItem : public UItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float HealAmount;
	
protected:
	virtual void Use(class AHero* Hero ) override;
};
