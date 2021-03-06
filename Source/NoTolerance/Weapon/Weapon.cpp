#include "Weapon.h"

UWeapon::UWeapon()
{
	FireRate = 1;
	Distance = 10000;
	SpreadAngle = 0;
}

void UWeapon::Shoot(AHero* Hero)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NOT IMPLEMENTED!"));
}

void UWeapon::StartAttacking(AHero* Hero)
{
	ShootingDelegate = FTimerDelegate::CreateUObject( this, &UWeapon::Shoot, Hero);
	GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, ShootingDelegate, FireRate, true, 0);
}

void UWeapon::StopAttacking()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
}

bool UWeapon::Equals(UWeapon* Weapon)
{
	return DisplayName.EqualTo(Weapon->DisplayName);
}
