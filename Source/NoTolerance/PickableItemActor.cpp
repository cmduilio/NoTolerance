// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemActor.h"

#include "Hero.h"

// Sets default values
APickableItemActor::APickableItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	AddOwnedComponent(SphereComponent);
}

// Called when the game starts or when spawned
void APickableItemActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableItemActor::OnOverlapBegin);
}

void APickableItemActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlaping!"));
	OnPickup(Cast<AHero>(OtherActor));
}

void APickableItemActor::OnPickup(AHero* Hero)
{
}
