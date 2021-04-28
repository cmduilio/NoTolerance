// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ThrowableItem.h"
#include "NoTolerance/Actor/ExplosionActor.h"

#include "ExplosiveItem.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API UExplosiveItem : public UThrowableItem
{
	GENERATED_BODY()
	
protected:
	virtual void Use(class AHero* Hero ) override;
	virtual void Use(class AActor* Container ) override;
	FTimerHandle ExplosionTimerHandle;
	FTimerDelegate ExplosionDelegate;
	void Explode(AActor* Container);
};
