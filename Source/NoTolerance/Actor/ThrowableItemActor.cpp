// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableItemActor.h"

// Sets default values
AThrowableItemActor::AThrowableItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetVisibility(true, true);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName(TEXT("PlayerShot"));

	RootComponent = StaticMeshComponent;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
	
	//AddOwnedComponent(StaticMeshComponent);

}

// Called when the game startheros or when spawned
void AThrowableItemActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AThrowableItemActor::OnOverlapBegin);
}

void AThrowableItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnHit(OtherActor);
}

void AThrowableItemActor::OnHit(AActor* Actor)
{
}

