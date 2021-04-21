#pragma once

#include "CoreMinimal.h"

#include "../Item.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickableItemActor.generated.h"

UCLASS()
class NOTOLERANCE_API APickableItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UItem* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

	UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnPickup(AHero* Hero);
	
};
