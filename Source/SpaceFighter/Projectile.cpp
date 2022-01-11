// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Enemy.h"
#include "Components/StaticMeshComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetConstraintMode(EDOFMode::XYPlane);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnDamage);
}

void AProjectile::OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass() == AEnemy::StaticClass())
	{
		ABaseFighter* Ship = Cast<ABaseFighter>(OtherActor);
		Ship->TakeDamage(ProjectileDamage);
		Destroy();
	}
}
