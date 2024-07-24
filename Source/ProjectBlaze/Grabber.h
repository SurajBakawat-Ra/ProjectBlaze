// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBLAZE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void DebugLine();
	void Grab();
	void Release();
	void SetupInputComponent();
	void FindPhysicsHandleComponent();
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	UInputComponent* GrabInput;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	const FHitResult GetFirstPhysicsBodyInReach();
};
