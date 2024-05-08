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
	// PullTrigger가 호출될 때, MuzzleFlashSocket의 위치에 ParticleSystem인 MuzzleFlash를 Spawn 시킨다.
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
			// FPointDamageEvent : 데미지의 종류 중 하나.
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			// TakeDamage
			// 데미지의 세기, 데미지 종류, 공격 명령을 내린 가해자, 데미지 전달을 위해 사용된 도구
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
	// 총을 소유한 캐릭터(폰)을 통해 해당 캐릭터(폰)을 Posses한 컨트롤러를 가져옴.
	// 현재 게임 상에서는 APlayerController(ShooterPlayerController), AAIController(ShooterAIController)가 있음.
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	// 디버그를 위한 카메라 모양의 쉐이프를 폰을 조종하는 컨트롤러의 위치에 그림.
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
