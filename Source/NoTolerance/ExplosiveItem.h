// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ExplosiveItem.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API UExplosiveItem : public UItem
{
	GENERATED_BODY()
	
protected:
	virtual void Use(class AHero* Hero ) override;
};
