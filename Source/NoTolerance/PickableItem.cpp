// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"

#include "Hero.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableItem::OnPickup(AHero* Hero)
{
}

