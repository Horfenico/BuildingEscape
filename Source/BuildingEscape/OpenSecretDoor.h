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
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float doorRaise = 5.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;
	AActor* actorThatOpens;
	AActor* owner;
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.f;
	float lastDoorOpenTime;
	FVector originalLoc;

		
	
};
