// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"

// Sets default values for this component's properties
UHealthSystem::UHealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthSystem::Heal(float Amount)
{
	Health += Amount;
}

void UHealthSystem::TakeDamage(float Damage)
{
	Health -= Damage;

	if(IsDead())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pepe!"));
	}
}

bool UHealthSystem::IsDead()
{
	return Health <= 0;	
}