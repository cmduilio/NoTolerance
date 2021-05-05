#include "Hero.h"

#include "../Item/ExplosiveItem.h"
#include "../Component/InventoryComponent.h"
#include "../Item/Item.h"
#include "../Actor/ThrowableItemActor.h"
#include "Engine/World.h"

// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	AddOwnedComponent(HealthComponent);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
	AddOwnedComponent(WeaponComponent);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
	AddOwnedComponent(InventoryComponent);
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
	HealthComponent->TakeDamage(Damage);
}

void AHero::UseItem(UItem* Item)
{
	Item->Use(this);
}

void AHero::UseSelectedItem()
{
	if(InventoryComponent->Items.Num() > 0)
	{
		InventoryComponent->Items[0]->Use(this);
		InventoryComponent->RemoveItem(InventoryComponent->Items[0]);
	}
}

void AHero::ThrowItem()
{
	if(InventoryComponent->ThrowableItem)
	{
		FVector SpawnLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * 20 + Camera->GetRightVector() * 20;
		FActorSpawnParameters SpawnParameters;
		//AThrowableItemActor* grenade = CreateDefaultSubobject<AThrowableItemActor>("Grenade");
		AThrowableItemActor* grenade = GetWorld()->SpawnActor<AThrowableItemActor>(
			AThrowableItemActor::StaticClass(), SpawnLocation, Camera->GetComponentRotation(),
			SpawnParameters);

		grenade->Item = DuplicateObject(InventoryComponent->ThrowableItem, InventoryComponent->ThrowableItem->GetOuter());
		//grenade->Item = InventoryComponent->ThrowableItem;
		//InventoryComponent->ThrowableItem = nullptr;
		grenade->StaticMeshComponent->SetStaticMesh(grenade->Item->PickupMesh);
		
		grenade->StaticMeshComponent->AddForce(Camera->GetForwardVector() * 100000 * grenade->StaticMeshComponent->GetMass());

		grenade->Item->Use(grenade);
		//InventoryComponent->ThrowableItem = nullptr;
		
		//grenade->StaticMeshComponent->SetWorldLocation(Camera->GetComponentLocation());

		//GetWorld()->SpawnActor<AActor>(Actor, Camera->GetComponentLocation(), Camera->GetComponentRotation(), SpawnParameters);
		//InventoryComponent->ThrowableItem
	}
}
