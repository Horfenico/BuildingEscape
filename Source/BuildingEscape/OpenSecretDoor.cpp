// Copyright Ethereal Games 2016

#include "BuildingEscape.h"
#include "OpenSecretDoor.h"


// Sets default values for this component's properties
UOpenSecretDoor::UOpenSecretDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenSecretDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	originalLoc = owner->GetActorLocation();
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenSecretDoor::OpenSecretDoor()
{
	FVector location = owner->GetActorLocation();
	if (location.Z < 320)
	{
		location.Z += doorRaise;
		owner->SetActorLocation(location);
	}
}

void UOpenSecretDoor::CloseSecretDoor()
{
	FVector location = owner->GetActorLocation();
	if (location.Z > originalLoc.Z)
	{
		location.Z -= doorRaise;
		owner->SetActorLocation(location);
	}
}


// Called every frame
void UOpenSecretDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(actorThatOpens))
	{
		OpenSecretDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	{
		CloseSecretDoor();
	}
}

