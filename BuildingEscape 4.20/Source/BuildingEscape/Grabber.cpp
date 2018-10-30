// Fill out your copyright notice in the Description page of Project Settings.

#define OUT
#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber active"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Get player view point this tick
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("X: %f  Y: %f  Z: %f  Pitch: %f  Yaw: %f  Roll: %f"),
	//	location.X,location.Y,location.Z,rotation.Pitch,rotation.Yaw,rotation.Roll);

	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector()*Reach;

	// Draw a red trace in the world to visualize
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		(uint8)'\000',
		1.f
	);

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
}

