// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableItemActor.h"

// Sets default values
AThrowableItemActor::AThrowableItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	AddOwnedComponent(SphereComponent);

}

// Called when the game starts or when spawned
void AThrowableItemActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AThrowableItemActor::OnOverlapBegin);
}

void AThrowableItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlaping!"));
	
	OnHit(OtherActor);
}

void AThrowableItemActor::OnHit(AActor* Actor)
{
}

