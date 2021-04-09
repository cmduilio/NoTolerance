// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "HealingPickableItem.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API AHealingPickableItem : public APickableItem
{
	GENERATED_BODY()

public:
	virtual void OnPickup(AHero* Hero) override;
	
};
