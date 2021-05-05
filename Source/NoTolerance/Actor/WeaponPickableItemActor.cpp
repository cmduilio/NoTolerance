#include "WeaponPickableItemActor.h"
#include "../Hero/Hero.h"
#include "NoTolerance/Item/WeaponItem.h"
#include "NoTolerance/Weapon/GunWeapon.h"

void AWeaponPickableItemActor::OnPickup(AHero* Hero)
{
	UWeaponItem* WeaponItem = Cast<UWeaponItem>(Item);
	if(WeaponItem)
	{
		UGunWeapon* GunWeapon = Cast<UGunWeapon>(Hero->WeaponComponent->Weapon);
		GunWeapon->AddAmmo(WeaponItem->Ammo);
		Destroy();
	}
}
