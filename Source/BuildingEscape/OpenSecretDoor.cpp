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
	
}

void UOpenSecretDoor::OpenSecretDoor()
{
	FVector location = owner->GetActorLocation();
	if (location.Z < doorRaise)
	{
		location.Z += 5.f;
		owner->SetActorLocation(location);
	}
}

void UOpenSecretDoor::CloseSecretDoor()
{
	FVector location = owner->GetActorLocation();
	if (location.Z > originalLoc.Z)
	{
		location.Z -= 5.f;
		owner->SetActorLocation(location);
	}
}

float UOpenSecretDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;
	//Find all overlapping actors
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(OUT overlappingActors);
	//Iterate through them, adding their masses
	for (const auto* i : overlappingActors)
	{
		totalMass += i->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *i->GetName())
	}
	return totalMass;
}


// Called every frame
void UOpenSecretDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > triggerWeight)
	{
		OpenSecretDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	{
		CloseSecretDoor();
	}
}

