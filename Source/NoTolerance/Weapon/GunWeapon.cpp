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

		UHealthComponent* EnemyHealthComponent = hitInfo.GetActor()->FindComponentByClass<UHealthComponent>();
		
		if(EnemyHealthComponent)
		{
			EnemyHealthComponent->TakeDamage(1);
		}
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MISS!"));
	}
}
