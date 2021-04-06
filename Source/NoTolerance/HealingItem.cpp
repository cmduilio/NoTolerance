// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"

#include "Hero.h"

void UHealingItem::Use(AHero* Hero)
{
	Hero->HealthSystem->Heal(HealAmount);
}
