// Copyright Ethereal Games 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber initiated. Standing by..."));	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector location;
	FRotator rotation;

	// Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);

	//Log view point every tick
	/*UE_LOG(LogTemp, Warning, TEXT("Player is at location: %s and rotation: %s"), *location.ToString(), *rotation.ToString())*/
	FVector lineTraceEnd = location + (rotation.Vector() * reach);

	//Draw red trace in world to visualize
	DrawDebugLine(GetWorld(), location, lineTraceEnd, FColor::Red, false, 0.f, 0, 10.f);
	//Ray-cast out to reach distance

	//See what we hit
}

