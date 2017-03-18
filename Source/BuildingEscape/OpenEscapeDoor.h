// Copyright Ethereal Games 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenEscapeDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenEscapeDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenEscapeDoor();
	void OpenEscapeDoor();
	void CloseEscapeDoor();
	bool EscapeTriggered();
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
	UPROPERTY(VisibleAnywhere)
	FString escapeActor = "SM_EscapeStatue";
	AActor* owner = nullptr;
	FVector originalLoc;
	
};
