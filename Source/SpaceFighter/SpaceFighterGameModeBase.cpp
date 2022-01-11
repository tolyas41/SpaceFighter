// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceFighterGameModeBase.h"
#include "Enemy.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceFighterPawn.h"

void ASpaceFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (isSinglePlay)
	{
		FTimerHandle MemberTimerHandle;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ASpaceFighterGameModeBase::SpawnEnemy, SpawnRate, true, 1.0f);
		PlayerPawn = Cast<ASpaceFighterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}
}

void ASpaceFighterGameModeBase::SpawnEnemy()
{
	if (!PlayerPawn->IsActorBeingDestroyed())
	{
		FVector SpawnLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() + FVector(FMath::RandRange(-SpawnArea, SpawnArea), FMath::RandRange(-SpawnArea, SpawnArea), 0);
		GetWorld()->SpawnActor<AEnemy>(EnemyToSpawn, SpawnLocation, FRotator(0, 0, 0));
	}
}
