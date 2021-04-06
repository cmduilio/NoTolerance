#include "WeaponComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GunWeapon.h"
#include "HealthSystem.h"

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