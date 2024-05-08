// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Projectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void AGun::PullTrigger()
{
	// PullTrigger�� ȣ��� ��, MuzzleFlashSocket�� ��ġ�� ParticleSystem�� MuzzleFlash�� Spawn ��Ų��.
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());

	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return;

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess)
	{
		// DrawDebugLine(GetWorld(), ViewPointLocation, HitResult.ImpactPoint, FColor::Red, true);
		// DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			// FPointDamageEvent : �������� ���� �� �ϳ�.
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			// TakeDamage
			// �������� ����, ������ ����, ���� ����� ���� ������, ������ ������ ���� ���� ����
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AGun::ProjectileSpawnPointLocation()
{
	return ProjectileSpawnPoint->GetComponentLocation();
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	// ���� ������ ĳ����(��)�� ���� �ش� ĳ����(��)�� Posses�� ��Ʈ�ѷ��� ������.
	// ���� ���� �󿡼��� APlayerController(ShooterPlayerController), AAIController(ShooterAIController)�� ����.
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	// ����׸� ���� ī�޶� ����� �������� ���� �����ϴ� ��Ʈ�ѷ��� ��ġ�� �׸�.
	// DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90, 2, FColor::Red, true);

	FVector End = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
	ShotDirection = -ViewPointRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, ViewPointLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}
