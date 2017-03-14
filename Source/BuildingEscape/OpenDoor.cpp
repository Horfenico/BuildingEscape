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
	//set actor that opens to play body
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	//Create Rotator
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
	if (pressurePlate->IsOverlappingActor(actorThatOpens))
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	{
		CloseDoor();
	}
}

