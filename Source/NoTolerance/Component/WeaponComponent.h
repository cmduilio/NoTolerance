#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Weapon/Weapon.h"
#include "NoTolerance/Item/WeaponItem.h"

#include "WeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTOLERANCE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TagName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<class UWeapon*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentWeapon;

	UWeapon* FindWeapon(class UWeaponItem* WeaponItem);
	UWeapon* GetCurrentWeapon();
	void ChangeWeapon(int Value);
	void AddWeapon(UWeapon* Weapon);
};