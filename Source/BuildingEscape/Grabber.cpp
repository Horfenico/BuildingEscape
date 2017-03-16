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

	///Look for physics handle
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Warning! Physics handle for %s not found."), *GetOwner()->GetName())
	}

	///Look for input component
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input)
	{
		///Bind the input action
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp,Error, TEXT("Warning! No Input Componenet on %s."), *GetOwner()->GetName())
	}
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
	//DrawDebugLine(GetWorld(), location, lineTraceEnd, FColor::Red, false, 0.f, 0, 10.f);

	//Set up query parameters
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());

	//line trace(Ray-cast) out to reach distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, location, lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams);
		
	//See what we hit
	AActor* actorHit = hit.GetActor();
	if (actorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *actorHit->GetName())
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed."))
}

