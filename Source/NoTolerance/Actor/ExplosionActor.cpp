// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionActor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

// Sets default values
AExplosionActor::AExplosionActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(RootComponent);
	//AddOwnedComponent(RadialForceComponent);

	ConstructorHelpers::FObjectFinder<UParticleSystem> Explotion(TEXT("ParticleSystem'/Engine/Tutorial/SubEditors/TutorialAssets/TutorialParticleSystem.TutorialParticleSystem'"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->SetTemplate(Explotion.Object);
	ParticleSystemComponent->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetWorldRotation(FRotator(0,0,0));
	
	//AddOwnedComponent(ParticleSystemComponent);
	
}

// Called when the game starts or when spawned
void AExplosionActor::BeginPlay()
{
	Super::BeginPlay();

	RadialForceComponent->Radius = 300;
	RadialForceComponent->ImpulseStrength = 300000;
	RadialForceComponent->ForceStrength = 1000;

	RadialForceComponent->FireImpulse();
	SetLifeSpan(3);
	
}

