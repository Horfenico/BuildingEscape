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
	GetPlayerViewPoint();

	///Log view point every tick
	/*UE_LOG(LogTemp, Warning, TEXT("Player is at location: %s and rotation: %s"), *location.ToString(), *rotation.ToString())*/

	//If physics handle is attached
	if (physicsHandle)
	{
		//if component grabbed
		if (physicsHandle->GrabbedComponent)
		{
			//Move the object we're holding each frame
			physicsHandle->SetTargetLocation(GetLineTraceEnd());
		}
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed."));
	//Line trace and see if we reaach any actors with PhysicsBody set
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();
	//If we hit something attach physics handle
	//attach physics handle
	if (actorHit)
	{
		physicsHandle->GrabComponent(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Released."))
	physicsHandle->ReleaseComponent();

}

void UGrabber::GetPhysicsHandle()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Warning! Physics handle for %s not found."), *GetOwner()->GetName());
	}
}

void UGrabber::GetInput()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input)
	{
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Warning! No Input Componenet on %s."), *GetOwner()->GetName())
	}
}

void UGrabber::GetPlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);
}

FVector UGrabber::GetLineTraceEnd()
{
	return location + (rotation.Vector() * reach);
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	GetPlayerViewPoint();
	///Set up query parameters
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	///line trace(Ray-cast) out to reach distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, location, GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams);
	return hit;
}