#pragma once

#include "CoreMinimal.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class NOTOLERANCE_API UWeapon : public UObject
{
	GENERATED_BODY()
	
public:
	UWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Distance;

	virtual void Shoot(class AHero* Hero);
	void StartAttacking(class AHero* Hero);
	void StopAttacking();
	FTimerHandle ShootingTimerHandle;
	FTimerDelegate ShootingDelegate;
};
