// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include"Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurrent.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* PlayerTank;
	int32 TargetTurrents=0;
	APlayerControllerBase* PlayerControllerRef;

	int32 GetTargetTurrentCount();
	void HandleGameStart();
	void HandleGameOver(bool Playerwon);

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)void GameStart();
	UFUNCTION(BlueprintImplementableEvent)void GameOver(bool Playerwon);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))int32 StartDelay;
};
