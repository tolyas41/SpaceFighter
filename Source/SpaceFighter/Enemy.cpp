// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Bonus.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetConstraintMode(EDOFMode::XYPlane);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);


}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AEnemy::OnDamage);
	
	Health = MaxHealth;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AEnemy::TakeDamage(float DamageAmount)
{
	DamageAmount = FMath::Min(Health, DamageAmount);
	Health -= DamageAmount;
	if (Health == 0)
	{
		GetWorld()->SpawnActor<ABonus>(BonusClass, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}


bool AEnemy::Fire(bool FireCommand)
{
	if (FireCommand)
	{
		FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
		AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
		return true;
	}
	else
	{
		return false;
	}
}
