// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceFighterPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASpaceFighterPawn::ASpaceFighterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetConstraintMode(EDOFMode::XYPlane);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->AddLocalRotation(FRotator(-80.0f, 0, 0));
	SpringArmComponent->SetupAttachment(StaticMesh);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	
}

void ASpaceFighterPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
	
	Health = MaxHealth;
}

void ASpaceFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorLocation().ToString());
	FHitResult HitResult;
	PlayerControllerRef->GetHitResultUnderCursor(
		ECollisionChannel::ECC_Visibility,
		false,
		HitResult);

	DrawDebugSphere(
		GetWorld(),
		HitResult.ImpactPoint,
		25.f,
		12,
		FColor::Red,
		false,
		-1.f);
	Rotate(HitResult.ImpactPoint);
}

void ASpaceFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASpaceFighterPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceFighterPawn::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceFighterPawn::Fire);

}

void ASpaceFighterPawn::MoveForward(float MoveValue)
{
	AddMovementInput(GetActorForwardVector(), MoveValue);
}

void ASpaceFighterPawn::MoveRight(float MoveValue)
{
	AddMovementInput(GetActorRightVector(), MoveValue);
}

void ASpaceFighterPawn::Rotate(FVector LookAtTarget)
{
	//MoveValue *= 0.4f;
	//AddControllerYawInput(MoveValue);
	FVector ToTarget = LookAtTarget - StaticMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	StaticMesh->SetWorldRotation(LookAtRotation);

}

void ASpaceFighterPawn::Fire()
{
	FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
	AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);

}

void ASpaceFighterPawn::TakeDamage(float DamageAmount)
{
	DamageAmount = FMath::Min(Health, DamageAmount);
	Health -= DamageAmount;
	if (Health == 0)
		Destroy();
}
