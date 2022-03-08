// Copyright Cindy C 2022

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
			CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, DoorOpenSpeed);
	FRotator open = FRotator::ZeroRotator;
	open.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(open);
}

void UOpenDoor::CloseDoor(float deltaTime)
{
	FRotator open = GetOwner()->GetActorRotation();
	open.Yaw = CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, deltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRotation(open);
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has open door component on it, but no pressureplate set."), *(GetOwner()->GetName()));
	}
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}
