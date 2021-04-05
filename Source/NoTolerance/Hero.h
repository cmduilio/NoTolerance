// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "HealthSystem.h"
#include "Gun.h"
#include "Hero.generated.h"

UCLASS()
class NOTOLERANCE_API AHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;
	FTimerHandle ShootingTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGun Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthSystem* HealthSystem;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void RotateYaw(float value);
	void RotatePitch(float value);
	void StartShooting();
	void StopShooting();
	void Shoot();
	void OnDamage(float Damage);
};
