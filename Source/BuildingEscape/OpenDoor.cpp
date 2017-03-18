// Copyright Ethereal Games 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// Find Owning Actor
	owner = GetOwner();
	originalRot = owner->GetActorRotation();
	if (!pressurePlate)
		UE_LOG(LogTemp, Error, TEXT("No Pressure Plate Assigned to Actor %s."), *owner->GetName());
}

void UOpenDoor::OpenDoor()
{
	////Create Rotator
	FRotator rotation = owner->GetActorRotation();
	if (rotation.Yaw > openAngle)
	{
		rotation.Yaw -= 5.f;

		//Set Door Rotation
		owner->SetActorRotation(rotation);
	}
}

void UOpenDoor::CloseDoor()
{
	//Create Rotator
	FRotator rotation = owner->GetActorRotation();
	if (rotation.Yaw < originalRot.Yaw)
	{
		rotation.Yaw += 5.f;

		//Set Door Rotation
		owner->SetActorRotation(rotation);
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	if (GetTotalMassOfActorsOnPlate() > triggerWeight) 
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
		//OnOpen.Broadcast();
	}
	
	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	//else
	{
		CloseDoor();
		//OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	if (!pressurePlate)
		return totalMass;
	//Find all overlapping actors
	pressurePlate->GetOverlappingActors(OUT overlappingActors);
	//Iterate through them, adding their masses
	for (const auto* i : overlappingActors)
	{
		totalMass += i->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp,Warning,TEXT("Actor: %s"), *i->GetName())

	}
	return totalMass;
}

