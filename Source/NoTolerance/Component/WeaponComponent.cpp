#include "WeaponComponent.h"
#include "../Weapon/GunWeapon.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	TagName = 3;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

UWeapon* UWeaponComponent::FindWeapon(UWeaponItem* WeaponItem)
{
	bool Found = false;
	int Index = 0;
	while(Index < Weapons.Num() && !Found)
	{
		Found = WeaponItem->Equals(Weapons[Index]->DisplayName);
		Index++;
	}
	
	return Found ? Weapons[Index - 1] : nullptr;  
}

UWeapon* UWeaponComponent::GetCurrentWeapon()
{
	return Weapons[CurrentWeapon];
}

void UWeaponComponent::ChangeWeapon(int Value)
{
	CurrentWeapon = (CurrentWeapon + Value) % Weapons.Num();
}

void UWeaponComponent::AddWeapon(UWeapon* Weapon)
{
	Weapons.Add(Weapon);	
}

