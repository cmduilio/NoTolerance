#include "Weapon.h"

UWeapon::UWeapon()
{
	FireRate = 1;
}

void UWeapon::Shoot(AHero* Hero)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NOT IMPLEMENTED!"));
}

void UWeapon::StartAttacking(AHero* Hero)
{
	ShootingDelegate = FTimerDelegate::CreateUObject( this, &UWeapon::Shoot, Hero);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attacking Weapon!"));
	//Shoot();
	GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, ShootingDelegate, FireRate, true, 0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}

void UWeapon::StopAttacking()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
}

