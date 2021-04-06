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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	virtual void Shoot();
	void StartAttacking();
	void StopAttacking();
	FTimerHandle ShootingTimerHandle;
};
