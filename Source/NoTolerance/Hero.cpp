#include "Hero.h"
 
#include "InventorySystem.h"
#include "Item.h"
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Shooting hero!"));
	WeaponComponent->Weapon->StartAttacking(this);
}

void AHero::StopShooting()
{
	WeaponComponent->Weapon->StopAttacking();
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
