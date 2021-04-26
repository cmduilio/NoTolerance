// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingPickableItemActor.h"

#include "../Hero/Hero.h"

void AHealingPickableItemActor::OnPickup(AHero* Hero)
{
	if(Item && Hero->HealthComponent->Health < Hero->HealthComponent->MaxHealth)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Using Item!"));
		Item->Use(Hero);
		Destroy();
	}
}
