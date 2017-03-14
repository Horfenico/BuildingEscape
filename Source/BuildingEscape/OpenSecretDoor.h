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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenSecretDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float doorRaise = 5.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;
	AActor* actorThatOpens;

		
	
};
