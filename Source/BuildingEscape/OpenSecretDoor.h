// Copyright Ethereal Games 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenSecretDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenSecretDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenSecretDoor();
	void OpenSecretDoor();
	void CloseSecretDoor();
	float GetTotalMassOfActorsOnPlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float doorRaise = 320.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 0.5f;
	UPROPERTY(EditAnywhere)
	float triggerWeight = 80.f;
	AActor* owner = nullptr;
	float lastDoorOpenTime;
	FVector originalLoc;

		
	
};
