// Copyright Ethereal Games 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	GetPhysicsHandle();
	GetInput();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If physics handle is attached
	//Move the object we're holding each frame

	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed."));

	//Line trace and see if we reaach any actors with PhysicsBody set
	GetFirstPhysicsBodyInReach();
	//If we hit something attach physics handle
	//TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Released."))
	//TODO release physics handle

}

void UGrabber::GetPhysicsHandle()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
	{
		///Physics handle found

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Warning! Physics handle for %s not found."), *GetOwner()->GetName())
	}
}

void UGrabber::GetInput()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input)
	{
		///Bind the input action
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Warning! No Input Componenet on %s."), *GetOwner()->GetName())
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector location;
	FRotator rotation;

	/// Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);

	///Log view point every tick
	/*UE_LOG(LogTemp, Warning, TEXT("Player is at location: %s and rotation: %s"), *location.ToString(), *rotation.ToString())*/
	FVector lineTraceEnd = location + (rotation.Vector() * reach);

	///Set up query parameters
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());

	///line trace(Ray-cast) out to reach distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, location, lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams);

	///See what we hit
	AActor* actorHit = hit.GetActor();
	if (actorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *actorHit->GetName());
	}
	return FHitResult();
}

