// Copyright Ethereal Games 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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
	UPROPERTY(EditAnywhere)
	float speed = 100.f;
	//how far ahead of the player can we reach
	float reach = 100.f;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* input = nullptr;
	UStaticMeshComponent* move = nullptr;
	USphereComponent* lock = nullptr;
	FVector location;
	FVector lineTraceEnd;
	FRotator rotation;
	//Ray-cast and grab what's in reach
	void Grab();
	void Release();
	void Shoot();
	void RotateStart();
	void Rotate();
	void RotateEnd();
	void GetPhysicsHandle();
	void GetInput();
	void GetPlayerViewPoint();
	bool rotateOn = false;
	FVector oldLoc = FVector(0, 0, 0);
	FRotator oldRot = FRotator(0, 0, 0);
	APlayerCameraManager* camMan = nullptr;

	FVector GetLineTraceEnd();

	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
};
