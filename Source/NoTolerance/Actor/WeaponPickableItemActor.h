// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItemActor.h"
#include "WeaponPickableItemActor.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API AWeaponPickableItemActor : public APickableItemActor
{
	GENERATED_BODY()
	
public:
	virtual void OnPickup(AHero* Hero) override;
};
