// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveItem.h"


void UExplosiveItem::Use(AHero* Hero)
{
	//ExplosionDelegate = FTimerDelegate::CreateUObject( this, &UExplosiveItem::Explode, Hero);
	//GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle,this, &UExplosiveItem::Explode, 5, false);
}
void UExplosiveItem::Use(AActor* Container)
{
	ExplosionDelegate = FTimerDelegate::CreateUObject(this, &UExplosiveItem::Explode, Container);
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, ExplosionDelegate, 2, false);
}

void UExplosiveItem::Explode(AActor* Container)
{
	FVector SpawnLocation = Container->GetActorLocation();
	FActorSpawnParameters SpawnParameters;
	
	AExplosionActor* ExplosionActor = GetWorld()->SpawnActor<AExplosionActor>(
		AExplosionActor::StaticClass(), SpawnLocation, FRotator(0,0,0),
		SpawnParameters);
	
	ExplosionActor->Initialize(300, 10);
	
	Container->Destroy();
}

