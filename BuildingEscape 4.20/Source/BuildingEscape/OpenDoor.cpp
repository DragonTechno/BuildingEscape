// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorOpener = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::RotateDoor(float rotation,float speed)
{
	// Find the owning Actor
	AActor* Owner = GetOwner();

	float OldYaw = Owner->GetActorRotation().Yaw;
	
	if (speed < 0)
	{
		if (OldYaw + speed < rotation)
		{
			speed = rotation - OldYaw;
		}
	}
	else
	{
		if (OldYaw + speed > rotation)
		{
			speed = rotation - OldYaw;
		}
	}
	if (abs(OldYaw - rotation) < DoorSpeed)
	{
		speed = 0;
	}

	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, OldYaw+speed, 0.f);

	// Set the rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check the trigger volume
	if (PressurePlate->IsOverlappingActor(DoorOpener))
	{
		open = true;
		RotateDoor(OpenAngle, DoorSpeed);
	}
	else if(!PressurePlate->IsOverlappingActor(DoorOpener))
	{
		open = false;
		RotateDoor(0., -DoorSpeed);
	}
}

