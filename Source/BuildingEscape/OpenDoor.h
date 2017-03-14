// Copyright Ethereal Games 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	float openAngle = 0.5f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 5.f;
	float lastDoorOpenTime;
	AActor* actorThatOpens;
	AActor* owner;
	FRotator originalRot;
		
	
};
