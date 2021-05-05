// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NOTOLERANCE_API UGunWeapon : public UWeapon
{
	GENERATED_BODY()

public:
	UGunWeapon();
	virtual void Shoot(class AHero* Hero) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmo;

	void AddAmmo(int Ammo);
};
