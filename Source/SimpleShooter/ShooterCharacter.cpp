// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


bool AShooterCharacter::IsDead() const 
{
	return CurrHealth <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return CurrHealth / MaxHealth;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrHealth = MaxHealth;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::LeftShift, EInputEvent::IE_Pressed, this, &AShooterCharacter::ShiftPressed);
	PlayerInputComponent->BindKey(EKeys::LeftShift, EInputEvent::IE_Released, this, &AShooterCharacter::ShiftReleased);
	PlayerInputComponent->BindAxis(TEXT("Move Forward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Look Right"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInvestigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInvestigator, DamageCauser);
	DamageApplied -= Defence;
	if (DamageApplied < 0) DamageApplied = 0;
	CurrHealth -= DamageApplied;
	if (CurrHealth < 0) CurrHealth = 0;
	UE_LOG(LogTemp, Warning, TEXT("%s : %f (Damage : %f)"), *GetActorNameOrLabel(), CurrHealth, DamageApplied);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	return DamageApplied;
}

void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * (bShiftPressed ? Value : Value * 0.5));
}

void AShooterCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector()* (bShiftPressed ? Value : Value * 0.5));
}

void AShooterCharacter::Shoot()
{
	if (Gun != nullptr)
	{
		Gun->PullTrigger();
	}
}

void AShooterCharacter::ShiftPressed()
{
	bShiftPressed = true;
	UE_LOG(LogTemp, Warning, TEXT("Shift Pressed!!"));
}

void AShooterCharacter::ShiftReleased()
{
	bShiftPressed = false;
	UE_LOG(LogTemp, Warning, TEXT("Shift Released!!"));
}
