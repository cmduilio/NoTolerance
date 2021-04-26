// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"

#include "../Hero/Hero.h"

void UHealingItem::Use(AHero* Hero)
{
	Hero->HealthComponent->Heal(HealAmount);
}
