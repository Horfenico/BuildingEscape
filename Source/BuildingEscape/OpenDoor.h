// Copyright Ethereal Games 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();
	float GetTotalMassOfActorsOnPlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;
private:
	UPROPERTY(EditAnywhere)
	float openAngle = 0.5f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 5.f;
	UPROPERTY(EditAnywhere)
	float triggerWeight = 10.f;
	float lastDoorOpenTime;
	AActor* owner = nullptr;
	FRotator originalRot;
		
	
};
