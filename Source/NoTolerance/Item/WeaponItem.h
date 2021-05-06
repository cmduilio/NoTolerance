#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "NoTolerance/Weapon/GunWeapon.h"

#include "WeaponItem.generated.h"

UCLASS()
class NOTOLERANCE_API UWeaponItem : public UItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGunWeapon* Weapon;
};
