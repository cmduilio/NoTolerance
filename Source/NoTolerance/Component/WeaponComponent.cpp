#include "WeaponComponent.h"
#include "../Weapon/GunWeapon.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	Weapon = CreateDefaultSubobject<UGunWeapon>("Weapon");
	TagName = 3;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}