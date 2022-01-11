// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseFighter.h"
#include "Enemy.generated.h"

//class UCapsuleComponent;
class UStaticMeshComponent;
class AProjectile;
class ABonus;

UCLASS()
class SPACEFIGHTER_API AEnemy : public ABaseFighter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	TSubclassOf<ABonus> BonusClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	USceneComponent* ProjectileSpawnPoint;

	UFUNCTION()
	void OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void TakeDamage(float DamageAmount) override;
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Fire", CompactNodeTitle = "New", Keywords = "new create blueprint"), Category = Game)
	bool Fire(bool FireCommand);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

};
