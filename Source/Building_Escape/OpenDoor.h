// Copyright Cindy C 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float deltaTime);

	float TotalMassOfActors() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenAngle;

	float DoorLastOpened = 0.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoors = 60.0f;
};
