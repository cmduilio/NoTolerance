#include "WeaponComponent.h"
#include "../GunWeapon.h"
// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	Weapon = CreateDefaultSubobject<UGunWeapon>("Gun");
	TagName = 3;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}