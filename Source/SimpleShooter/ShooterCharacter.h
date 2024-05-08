// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInvestigator, AActor* DamageCauser);
	void Shoot();

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	

	void ShiftPressed();
	void ShiftReleased();

	bool bShiftPressed = false;
	// void LookUp(float Value);
	// void LookRight(float Value);

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float CurrHealth;

	UPROPERTY(EditAnywhere)
	float Defence = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	class AGun* Gun;

};
