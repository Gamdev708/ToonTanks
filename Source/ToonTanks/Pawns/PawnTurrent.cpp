// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurrent.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurrent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }
	RotateTurrent(PlayerPawn->GetActorLocation());
}

void APawnTurrent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurrent::CheckFireCondition, FireRate,true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurrent::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void APawnTurrent::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) { return; }
	if (ReturnDistanceToPlayer() <= FireRange) 
	{ 
		Fire(); 
	}
	
}

float APawnTurrent::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) { return 0.0f; }
	
	return  FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

