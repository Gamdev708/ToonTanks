// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include"Kismet/GameplayStatics.h"
#include"ToonTanks/Actors/ProjectileBase.h"
#include"ToonTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capusle Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);

	HealthCompnent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APawnBase::RotateTurrent(FVector LookAtTarget)
{
	//Update TurrentMesh rotation to face towards the LookAtTarget passed in the Child Classes
	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurrentMesh->GetComponentLocation().Z);
	FVector StartLocation = TurrentMesh->GetComponentLocation();
	FRotator TurrentRotation = FVector(LookAtTargetClean-StartLocation).Rotation();
	TurrentMesh->SetWorldRotation(TurrentRotation);
	
	//Turrent Mesh
}

void APawnBase::Fire()
{
	//Get ProjectileSpawnPoint Location && Rotation->
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	//-----Universal Functionalt------
	//Play death effects particle,sound and cam shake
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
	//Then do Child ooveriide
	//----Pawn Turrent- Inform Gamemode Turrent Died->DestroySlef
	//----Pawn Tank- Inform Gamemode Player Died->Hide all comps and Stop movement
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

