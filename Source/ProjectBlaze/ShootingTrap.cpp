// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingTrap.h"
#include "BulletProjectile.h"

// Sets default values
AShootingTrap::AShootingTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootingTrap::BeginPlay()
{
	Super::BeginPlay();

	if(!PressurePlate){UE_LOG(LogTemp,Error,TEXT("Trap is missing pressure plate"))}
	if(!ActorThatTriggers){UE_LOG(LogTemp,Error,TEXT("Trap is missing triggering actor"))}
	
}

// Called every frame
void AShootingTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PressurePlate) { return; }
	if (!ActorThatTriggers){ return; }
	TriggerTrap();

}

void AShootingTrap::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			ABulletProjectile* const Projectile = World->SpawnActor<ABulletProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}

void AShootingTrap::TriggerTrap()
{
	if (PressurePlate->IsOverlappingActor(ActorThatTriggers)) { OnFire(); }
}



