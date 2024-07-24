// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MoveWeightPlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBLAZE_API UMoveWeightPlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveWeightPlatform();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(VisibleAnywhere)
		FVector InitLocation;

	UPROPERTY(VisibleAnywhere)
		FRotator InitRotation;

	UPROPERTY(EditAnywhere)
		FVector SetLocation;

	UPROPERTY(EditAnywhere)
		FRotator SetRotation;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;


	void MovePlatform();
	void ReturnPlatorm();
	float GetTotalMassOfActorOnPlate();

};
