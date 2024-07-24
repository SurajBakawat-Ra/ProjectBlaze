// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveWeightPlatform.h"
#define OUT

// Sets default values for this component's properties
UMoveWeightPlatform::UMoveWeightPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveWeightPlatform::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	InitLocation = Owner->GetActorLocation();
	InitRotation = Owner->GetActorRotation();

	if (!PressurePlate) { UE_LOG(LogTemp, Error, TEXT("%s is missing pressure plate"), *Owner->GetName()) }
	
}


// Called every frame
void UMoveWeightPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate) { return; }

	if (GetTotalMassOfActorOnPlate() > TriggerMass)
	{
		MovePlatform();
	}
	else
	{
		ReturnPlatorm();
	}
}

void UMoveWeightPlatform::MovePlatform()
{
	Owner->SetActorLocation(SetLocation); Owner->SetActorRotation(SetRotation);
}

void UMoveWeightPlatform::ReturnPlatorm()
{
	Owner->SetActorLocation(InitLocation); Owner->SetActorRotation(InitRotation);
}


float UMoveWeightPlatform::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverLappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	for (const auto* Actor : OverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
	}
	return TotalMass;
}
