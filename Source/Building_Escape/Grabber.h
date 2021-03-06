// Copyright Cindy C 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void FindPhysicsHandle();
	void SetupInputComponent();
	void Grab();
	void Release();
	FVector GetPlayerWorldPos() const;
	FVector GetPlayerReach() const;
	FHitResult GetFirstPhysicsBodyInReach() const;

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UPROPERTY() // 讓 UE 不要自動回收
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY() // 讓 UE 不要自動回收
	UInputComponent* InputComponent = nullptr;
};
