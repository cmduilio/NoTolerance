#include "Hero.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	HealthSystem = CreateDefaultSubobject<UHealthSystem>("HealthSystem");
	AddOwnedComponent(HealthSystem);
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("Horizontal", this, &AHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AHero::RotateYaw);
	PlayerInputComponent->BindAxis("Look", this, &AHero::RotatePitch);
	
	
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
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &AHero::Shoot, FireRate, true, 0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}

void AHero::StopShooting()
{
	GetWorldTimerManager().ClearTimer(ShootingTimerHandle);
}


void AHero::Shoot()
{
	FVector start = Camera->GetComponentLocation();
	FVector end = start + (Camera->GetForwardVector() * 100000);
	FHitResult hitInfo;

	//for(int i = 0; i < 7; i++){
	bool hit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_GameTraceChannel3);
	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 3);
	if(hit && hitInfo.GetActor() != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, hitInfo.GetActor()->GetName());

		UHealthSystem* EnemyHealthSystem = hitInfo.GetActor()->FindComponentByClass<UHealthSystem>();
		
		if(EnemyHealthSystem)
		{
			EnemyHealthSystem->TakeDamage(1);
		}
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MISS!"));
	}
}

void AHero::OnDamage(float Damage)
{
	HealthSystem->TakeDamage(Damage);
}
