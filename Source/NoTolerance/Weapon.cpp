#include "Weapon.h"

void UWeapon::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NOT IMPLEMENTED!"));
}

void UWeapon::StartAttacking()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attacking Weapon!"));
	GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeapon::Shoot, FireRate, true, 0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}

void UWeapon::StopAttacking()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
}

