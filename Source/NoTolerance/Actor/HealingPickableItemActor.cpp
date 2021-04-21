// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingPickableItemActor.h"

#include "../Hero.h"

void AHealingPickableItemActor::OnPickup(AHero* Hero)
{
	if(Item && Hero->HealthSystem->Health < Hero->HealthSystem->MaxHealth)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Using Item!"));
		Item->Use(Hero);
		Destroy();
	}
}
