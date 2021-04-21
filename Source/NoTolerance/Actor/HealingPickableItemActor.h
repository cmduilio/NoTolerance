// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItemActor.h"
#include "HealingPickableItemActor.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API AHealingPickableItemActor : public APickableItemActor
{
	GENERATED_BODY()

public:
	virtual void OnPickup(AHero* Hero) override;
	
};
