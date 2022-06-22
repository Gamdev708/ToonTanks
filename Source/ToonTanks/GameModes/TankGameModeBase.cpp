// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurrent.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include"Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();



	HandleGameStart();
}

/// <summary>
/// Check What type of Actor died.If turren or Ally. If Player-> goto lose condition
/// </summary>
/// <param name="DeadActor"></param>
void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor==PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnableState(false);
		}
	}
	else if(APawnTurrent* DestroyedTurrent = Cast<APawnTurrent>(DeadActor))
	{
		DestroyedTurrent->HandleDestruction();

		if (--TargetTurrents==0)
		{
			HandleGameOver(true);
		}
		
	}
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));
}

int32 ATankGameModeBase::GetTargetTurrentCount()
{
	TArray<AActor*> TurrentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurrent::StaticClass(), TurrentActors);
	return TurrentActors.Num();
}

/// <summary>
/// Intisialise the Start countdown,Turrent activation,pawnCheck..etc
/// </summary>
void ATankGameModeBase::HandleGameStart()
{
	//Get Turrent and Tank Details
	TargetTurrents = GetTargetTurrentCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnableState,true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle,PlayerEnableDelegate,StartDelay,false);
	}
}

/// <summary>
/// Seeif player has destroyed all turrents,Show win
/// else if plyaer died show loss
/// Call blueprint version Gameover(bool)
/// </summary>
/// <param name="Playerwon"></param>
void ATankGameModeBase::HandleGameOver(bool Playerwon)
{
	GameOver(Playerwon);
}



