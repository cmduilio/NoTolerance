#include "GunWeapon.h"
#include "HealthSystem.h"
#include "DrawDebugHelpers.h"
#include "Hero.h"

void UGunWeapon::Shoot(AHero* Hero)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Shooting GunWeapon!"));
	
	FVector start = Hero->Camera->GetComponentLocation();
	FVector end = start + (Hero->Camera->GetForwardVector() * 100000);
	FHitResult hitInfo;

	//for(int i = 0; i < 7; i++){
	bool hit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_GameTraceChannel3);
	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 3);
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
