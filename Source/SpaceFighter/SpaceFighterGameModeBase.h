// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceFighterGameModeBase.generated.h"


class AEnemy;
class ASpaceFighterPawn;

UCLASS()
class SPACEFIGHTER_API ASpaceFighterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AEnemy> EnemyToSpawn;

	void SpawnEnemy();

	ASpaceFighterPawn* PlayerPawn;
	UPROPERTY(EditAnywhere)
	float SpawnRate = 2.0f;
	UPROPERTY(EditAnywhere)
	float SpawnArea = 500.0f;
	UPROPERTY(EditAnywhere)
	bool isSinglePlay = true;
};
