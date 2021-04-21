#include "Hero.h"

#include "ExplosiveItem.h"
#include "Component/InventorySystem.h"
#include "Item.h"
#include "Actor/ThrowableItemActor.h"
#include "Engine/World.h"

// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	HealthSystem = CreateDefaultSubobject<UHealthSystem>("HealthSystem");
	AddOwnedComponent(HealthSystem);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
	AddOwnedComponent(WeaponComponent);

	InventorySystem = CreateDefaultSubobject<UInventorySystem>("InventorySystem");
	AddOwnedComponent(InventorySystem);
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("Horizontal", this, &AHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AHero::RotateYaw);
	PlayerInputComponent->BindAxis("Look", this, &AHero::RotatePitch);
	
	PlayerInputComponent->BindAction("Item", IE_Pressed, this, &AHero::UseSelectedItem);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHero::StartShooting);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AHero::StopShooting);
	
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHero::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHero::StopCrouching);
	
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AHero::ThrowItem);
}


void AHero::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AHero::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AHero::RotateYaw(float value)
{
	AddControllerYawInput(value * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AHero::RotatePitch(float value)
{
	AddControllerPitchInput(value * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AHero::StartShooting()
{
	WeaponComponent->Weapon->StartAttacking(this);
}

void AHero::StopShooting()
{
	WeaponComponent->Weapon->StopAttacking();
}

void AHero::StartCrouching()
{
	Crouch();
}

void AHero::StopCrouching()
{
	UnCrouch();
}

void AHero::OnDamage(float Damage)
{
	HealthSystem->TakeDamage(Damage);
}

void AHero::UseItem(UItem* Item)
{
	Item->Use(this);
}

void AHero::UseSelectedItem()
{
	if(InventorySystem->Items.Num() > 0)
	{
		InventorySystem->Items[0]->Use(this);
		InventorySystem->RemoveItem(InventorySystem->Items[0]);
	}
}

void AHero::ThrowItem()
{
	if(InventorySystem->ThrowableItem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Throwing!"));
		FVector SpawnLocation = Camera->GetComponentLocation() + Camera->GetRightVector() * 20;
		FActorSpawnParameters SpawnParameters;
		//AThrowableItemActor* grenade = CreateDefaultSubobject<AThrowableItemActor>("Grenade");
		AThrowableItemActor* grenade = GetWorld()->SpawnActor<AThrowableItemActor>(
			AThrowableItemActor::StaticClass(), SpawnLocation, Camera->GetComponentRotation(),
			SpawnParameters);
		
		grenade->Item = InventorySystem->ThrowableItem;
		//InventorySystem->ThrowableItem = nullptr;
		grenade->StaticMeshComponent->SetStaticMesh(grenade->Item->PickupMesh);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		                                 FString::SanitizeFloat(grenade->StaticMeshComponent->GetMass()));
		
		grenade->StaticMeshComponent->AddForce(Camera->GetForwardVector() * 200000 * grenade->StaticMeshComponent->GetMass());
		//grenade->StaticMeshComponent->SetWorldLocation(Camera->GetComponentLocation());

		//GetWorld()->SpawnActor<AActor>(Actor, Camera->GetComponentLocation(), Camera->GetComponentRotation(), SpawnParameters);
		//InventorySystem->ThrowableItem
	}
}
