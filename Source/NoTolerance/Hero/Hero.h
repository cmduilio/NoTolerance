// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "../Component/HealthComponent.h"
#include "../Component/WeaponComponent.h"

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
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* WeaponComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSprinting;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void RotateYaw(float value);
	void RotatePitch(float value);
	
	UFUNCTION(BlueprintCallable)
	void NextWeapon();

	UFUNCTION(BlueprintCallable)
	void PreviousWeapon();
	
	void StartShooting();
	void StopShooting();
	void StartSprinting();
	void StopSprinting();
	void StartCrouching();
	void StopCrouching();
	void UseSelectedItem();
	void ThrowItem();
	
	void OnDamage(float Damage);
	void UseItem(class UItem* Item);
};
