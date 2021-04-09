#pragma once

#include "CoreMinimal.h"

#include "Item.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

UCLASS()
class NOTOLERANCE_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UItem* Item;

	UFUNCTION(BlueprintCallable)
	void OnPickup(AHero* Hero);
	
};
