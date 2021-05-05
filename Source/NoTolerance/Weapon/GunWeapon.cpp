#include "GunWeapon.h"
#include "../Component/HealthComponent.h"
#include "DrawDebugHelpers.h"
#include "../Hero/Hero.h"
#include "Math/UnrealMathUtility.h"

UGunWeapon::UGunWeapon()
{
}

void UGunWeapon::Shoot(AHero* Hero)
{
	//for(int i = 0; i < 100; i++)
	//{
		if(CurrentAmmo > 0)
		{
			float alfaY = FMath::DegreesToRadians(FMath::FRandRange(-1 * SpreadAngle, SpreadAngle));
			float alfaZ = FMath::DegreesToRadians(FMath::FRandRange(-1 * SpreadAngle, SpreadAngle));
			FVector DeltaY = Hero->Camera->GetUpVector() * (FMath::Tan(alfaY) * Distance);
			FVector DeltaZ = Hero->Camera->GetRightVector() * (FMath::Tan(alfaZ) * Distance);
		
			FVector start = Hero->Camera->GetComponentLocation();
			FVector end = start + (Hero->Camera->GetForwardVector() * Distance) + DeltaY + DeltaZ;
		
			FHitResult hitInfo;

			FColor LineColor = FColor::Green;
			bool hit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_GameTraceChannel3);
			if(hit && hitInfo.GetActor() != nullptr)
			{
				LineColor = FColor::Red;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, hitInfo.GetActor()->GetName());

				UHealthComponent* EnemyHealthComponent = hitInfo.GetActor()->FindComponentByClass<UHealthComponent>();
		
				if(EnemyHealthComponent)
				{
					EnemyHealthComponent->TakeDamage(1);
				}
			}

			CurrentAmmo--;
			DrawDebugLine(GetWorld(), start + (Hero->Camera->GetForwardVector() * 100), end, LineColor, false, 20, 0, 1);
		}
	//}
}

void UGunWeapon::AddAmmo(int Ammo)
{
	CurrentAmmo = CurrentAmmo + Ammo >= MaxAmmo ? MaxAmmo : CurrentAmmo + Ammo; 
}
