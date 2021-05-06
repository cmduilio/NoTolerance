#include "WeaponPickableItemActor.h"
#include "../Hero/Hero.h"
#include "NoTolerance/Item/WeaponItem.h"
#include "NoTolerance/Weapon/GunWeapon.h"

void AWeaponPickableItemActor::OnPickup(AHero* Hero)
{
	UWeaponItem* WeaponItem = Cast<UWeaponItem>(Item);
	if(WeaponItem)
	{
		UWeapon* Weapon = Hero->WeaponComponent->FindWeapon(WeaponItem);
		if(Weapon){
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FoundWeapon!"));
	
			UGunWeapon* GunWeapon = Cast<UGunWeapon>(Weapon);
			GunWeapon->AddAmmo(WeaponItem->Ammo);
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Adding Weapon!"));
			Hero->WeaponComponent->AddWeapon(WeaponItem->Weapon);
		}
		Destroy();
	}
}
