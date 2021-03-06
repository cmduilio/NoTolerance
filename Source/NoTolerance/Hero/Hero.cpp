#include "Hero.h"

#include "../Item/ExplosiveItem.h"
#include "../Component/InventoryComponent.h"
#include "../Item/Item.h"
#include "../Actor/ThrowableItemActor.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "DrawDebugHelpers.h"

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
	
	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &AHero::OnViewportSizeChange);

	CrouchingTimeline = CreateDefaultSubobject<UTimelineComponent>("TimelineComponent");
	ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Blueprints/Player/CrouchingCurve.CrouchingCurve'"));
	CrouchingCurve = Curve.Object;
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	CrouchingTimeline->AddInterpFloat(CrouchingCurve, InterpFunction, FName(TEXT("Alpha")));
	CrouchingTimeline->SetLooping(false);

	CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
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
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &AHero::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &AHero::PreviousWeapon);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHero::StartShooting);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AHero::StopShooting);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHero::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHero::StopSprinting);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHero::StartJumping);
	
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

void AHero::NextWeapon()
{
	WeaponComponent->ChangeWeapon(1);
}

void AHero::PreviousWeapon()
{
	WeaponComponent->ChangeWeapon(-1);
}

void AHero::StartShooting()
{
	WeaponComponent->GetCurrentWeapon()->StartAttacking(this);
}

void AHero::StopShooting()
{
	WeaponComponent->GetCurrentWeapon()->StopAttacking();
}

void AHero::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200;
	IsSprinting = true;
}

void AHero::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
	IsSprinting = false;
}

void AHero::StartCrouching()
{
	CrouchingTimeline->Play();
	IsCrouching = true;
	//Crouch();
}

void AHero::StopCrouching()
{
	FHitResult HitInfo;
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0.0f, 0.0f, 200.0f);
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_GameTraceChannel3);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 20, 0, 1);
	if(!Hit)
	{
		CrouchingTimeline->Reverse();
		IsCrouching = false;
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, HitInfo.GetComponent()->GetName());
	}
	
	//UnCrouch();
}

void AHero::TimelineFloatReturn(float Value)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::Lerp(CapsuleHalfHeight, GetCharacterMovement()->CrouchedHalfHeight, Value));
}

void AHero::StartJumping()
{
	Jump();
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

void AHero::OnViewportSizeChange(FViewport* ViewPort, uint32 val)
{
	UpdateCrosshair();
}
