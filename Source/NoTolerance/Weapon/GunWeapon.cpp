#include "GunWeapon.h"
#include "../Component/HealthComponent.h"
#include "DrawDebugHelpers.h"
#include "../Hero/Hero.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "NoTolerance/Enemy/Enemy.h"
#include "Materials/Material.h"

UGunWeapon::UGunWeapon()
{
	ConstructorHelpers::FObjectFinder<UMaterial> Bullethole(TEXT("Material'/Game/Assets/Bullethole/M_Bullethole.M_Bullethole'"));
	BulletHole = Bullethole.Object;
	
	ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Blueprints/Weapons/SpreadCurve.SpreadCurve'"));
	CurveFloat = Curve.Object;
}

void UGunWeapon::Shoot(AHero* Hero)
{
	if(CurrentAmmo > 0)
	{
		for(int i = 0; i < Pellets; i++)
		{
			float Angle = FMath::DegreesToRadians(FMath::FRandRange(0, 360));
			float Radius = FMath::Tan(FMath::DegreesToRadians(SpreadAngle)) * Distance;
			//float RandomRadius = FMath::FRandRange(0, Radius);

			float RandomRadius = Radius * CurveFloat->GetFloatValue(FMath::FRandRange(0, 1));

			FVector DeltaY = Hero->Camera->GetUpVector() * RandomRadius * FMath::Cos(Angle);
			FVector DeltaZ = Hero->Camera->GetRightVector() * RandomRadius * FMath::Sin(Angle);
		
			FVector Start = Hero->Camera->GetComponentLocation();
			FVector End = Start + (Hero->Camera->GetForwardVector() * Distance) + DeltaY + DeltaZ;
		
			FHitResult HitInfo;

			FColor LineColor = FColor::Green;
			bool Hit = GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_GameTraceChannel3);
			if(Hit && HitInfo.GetActor() != nullptr)
			{
				LineColor = FColor::Red;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, HitInfo.GetActor()->GetName());

				UHealthComponent* EnemyHealthComponent = HitInfo.GetActor()->FindComponentByClass<UHealthComponent>();
		
				if(EnemyHealthComponent)
				{
					EnemyHealthComponent->TakeDamage(1);
				}
			}

			if(Hit && !Cast<AEnemy>(HitInfo.GetActor()))
			{
				UGameplayStatics::SpawnDecalAttached(BulletHole, FVector(5.0f, 5.0f, 6.0f),
					HitInfo.GetComponent(), HitInfo.BoneName,HitInfo.ImpactPoint, HitInfo.ImpactNormal.Rotation(),
					EAttachLocation::KeepWorldPosition, 3);   
			}
			
			//DrawDebugLine(GetWorld(), Start + (Hero->Camera->GetForwardVector() * 100), End, LineColor, false, 20, 0, 1);
		}
		
		CurrentAmmo--;
	}
	
}

void UGunWeapon::AddAmmo(int Ammo)
{
	CurrentAmmo = CurrentAmmo + Ammo >= MaxAmmo ? MaxAmmo : CurrentAmmo + Ammo; 
}
