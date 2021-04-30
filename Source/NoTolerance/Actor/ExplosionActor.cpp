// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionActor.h"

#include "NoTolerance/Enemy/Enemy.h"
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
	SetLifeSpan(3);
}

void AExplosionActor::Initialize(float Radius, float Damage)
{
	RadialForceComponent->Radius = Radius;
	RadialForceComponent->ImpulseStrength = 300000;
	RadialForceComponent->ForceStrength = 1000;

	FVector Start = this->GetActorLocation();
	FVector End = Start + (this->RadialForceComponent->GetForwardVector() * Radius) ;
	FCollisionShape MySphere = FCollisionShape::MakeSphere(RadialForceComponent->Radius); // 5M Radius
	TArray<FHitResult> OutResults;
	GetWorld()->SweepMultiByChannel(OutResults, Start, End, FQuat::Identity, ECC_GameTraceChannel3, MySphere);

	for(FHitResult hit : OutResults)
	{
		if(hit.GetActor() && Cast<AEnemy>(hit.GetActor()))
		{
			UHealthComponent* EnemyHealthComponent = hit.GetActor()->FindComponentByClass<UHealthComponent>();
			if(EnemyHealthComponent)
			{
				EnemyHealthComponent->TakeDamage(Damage);
			}
		}
	}
	RadialForceComponent->FireImpulse();
}
