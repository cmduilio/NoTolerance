#include "GunWeapon.h"
#include "HealthSystem.h"
#include "DrawDebugHelpers.h"
#include "Hero.h"
#include "Math/UnrealMathUtility.h"

UGunWeapon::UGunWeapon()
{
}

void UGunWeapon::Shoot(AHero* Hero)
{
	float alfaY = FMath::DegreesToRadians(FMath::FRandRange(-1 * SpreadAngle, SpreadAngle));
	float alfaZ = FMath::DegreesToRadians(FMath::FRandRange(-1 * SpreadAngle, SpreadAngle));
	FVector DeltaY = Hero->Camera->GetUpVector() * (FMath::Tan(alfaY) * Distance);
	FVector DeltaZ = Hero->Camera->GetRightVector() * (FMath::Tan(alfaZ) * Distance);
	
	FVector start = Hero->Camera->GetComponentLocation();
	FVector end = start + (Hero->Camera->GetForwardVector() * Distance) + DeltaY + DeltaZ;
	
	FHitResult hitInfo;

	//for(int i = 0; i < 7; i++){
	bool hit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_GameTraceChannel3);
	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 20.f);
	if(hit && hitInfo.GetActor() != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, hitInfo.GetActor()->GetName());

		UHealthSystem* EnemyHealthSystem = hitInfo.GetActor()->FindComponentByClass<UHealthSystem>();
		
		if(EnemyHealthSystem)
		{
			EnemyHealthSystem->TakeDamage(1);
		}
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MISS!"));
	}
}
