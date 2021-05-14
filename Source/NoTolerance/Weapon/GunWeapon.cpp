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
	if(CurrentAmmo > 0)
	{
		for(int i = 0; i < Pellets; i++)
		{
			float Angle = FMath::DegreesToRadians(FMath::FRandRange(0, 360));
			float Radius = FMath::Tan(FMath::DegreesToRadians(SpreadAngle)) * Distance;

			FVector DeltaY = Hero->Camera->GetUpVector() * Radius * FMath::Cos(Angle);
			FVector DeltaZ = Hero->Camera->GetRightVector() * Radius * FMath::Sin(Angle);
		
			FVector Start = Hero->Camera->GetComponentLocation();
			FVector End = Start + (Hero->Camera->GetForwardVector() * Distance) + DeltaY + DeltaZ;
		
			FHitResult HitInfo;

			FColor LineColor = FColor::Green;
			bool Hit = GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_GameTraceChannel3);
			if(Hit && HitInfo.GetActor() != nullptr)
			{
				LineColor = FColor::Red;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, HitInfo.GetActor()->GetName());

				UHealthComponent* EnemyHealthComponent = HitInfo.GetActor()->FindComponentByClass<UHealthComponent>();
		
				if(EnemyHealthComponent)
				{
					EnemyHealthComponent->TakeDamage(1);
				}
			}

			DrawDebugLine(GetWorld(), Start + (Hero->Camera->GetForwardVector() * 100), End, LineColor, false, 20, 0, 1);
		}
		
		CurrentAmmo--;
	}
	
}

void UGunWeapon::AddAmmo(int Ammo)
{
	CurrentAmmo = CurrentAmmo + Ammo >= MaxAmmo ? MaxAmmo : CurrentAmmo + Ammo; 
}
