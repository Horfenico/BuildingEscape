// Copyright Ethereal Games 2016

#include "BuildingEscape.h"
#include "OpenEscapeDoor.h"


// Sets default values for this component's properties
UOpenEscapeDoor::UOpenEscapeDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenEscapeDoor::OpenEscapeDoor()
{
	FVector location = owner->GetActorLocation();
	if (location.Z < doorRaise)
	{
		location.Z += 5.f;
		owner->SetActorLocation(location);
	}
}

void UOpenEscapeDoor::CloseEscapeDoor()
{
	FVector location = owner->GetActorLocation();
	if (location.Z > originalLoc.Z)
	{
		location.Z -= 5.f;
		owner->SetActorLocation(location);
	}
}

bool UOpenEscapeDoor::EscapeTriggered()
{
	TArray<AActor*> overlappingActors;
	if (!pressurePlate)
		return false;
	pressurePlate->GetOverlappingActors(OUT overlappingActors);
	for (const auto* i : overlappingActors)
	{
		if (i->GetName() == escapeActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Escape Actor Successfully placed."))
				return true;
		}
	}
	return false;
}


// Called when the game starts
void UOpenEscapeDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	originalLoc = owner->GetActorLocation();
	if (!pressurePlate)
		UE_LOG(LogTemp, Error, TEXT("No Pressure Plate Assigned to Actor %s."), *owner->GetName());
}



// Called every frame
void UOpenEscapeDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (EscapeTriggered())
		OpenEscapeDoor();
	else
		CloseEscapeDoor();
	
}

