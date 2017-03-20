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
	if (!physicsHandle) return;
	//if component grabbed
	if (physicsHandle->GrabbedComponent)
	{
		//Move the object we're holding each frame
		physicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
	if (rotateOn)
	{
		lock = GetOwner()->FindComponentByClass<USphereComponent>();
		if (!lock) return;
		//Lock player location and rotation so camera doesn't move while rotating object.
		lock->SetWorldLocation(oldLoc);
		GetWorld()->GetFirstPlayerController()->SetControlRotation(oldRot);
		Rotate();
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
	if (!physicsHandle) return;
	if (actorHit)
	{
		physicsHandle->GrabComponentAtLocationWithRotation(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), FRotator(0, 0, 0));
	}
}

void UGrabber::Release()
{
		if (!physicsHandle) return;
		UE_LOG(LogTemp, Warning, TEXT("Grab Key Released."))
		physicsHandle->ReleaseComponent();
}

void UGrabber::Shoot()
{
	if (!physicsHandle) return;
	if (physicsHandle->GrabbedComponent)
	{
		move = physicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UStaticMeshComponent>();
		if (!move)
		{
			UE_LOG(LogTemp, Error, TEXT("No Movement Component Attached."));
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Shoot Button Pressed."))
		Release();
		move->AddForce(speed * rotation.Vector(),NAME_None, true);
		UE_LOG(LogTemp, Warning, TEXT("Owner: %s"),  *move->GetName());	
	}
}

void UGrabber::RotateStart()
{
	if (!physicsHandle) return;
	if (physicsHandle->GrabbedComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rotate On."));
		rotateOn = true;
		oldLoc = GetOwner()->GetActorLocation();
		oldRot = GetWorld()->GetFirstPlayerController()->GetControlRotation();
	}
}

void UGrabber::Rotate()
{
	float mouseX;
	float mouseY;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(OUT mouseX, OUT mouseY);
	FRotator newRot(-mouseY, mouseX, 0);
	if (!physicsHandle) return;
	if (physicsHandle->GrabbedComponent)
	{
		physicsHandle->SetTargetRotation(newRot);
	}
}

void UGrabber::RotateEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Rotate Off."));
	rotateOn = false;
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
		input->BindAction("Shoot", IE_Pressed, this, &UGrabber::Shoot);
		input->BindAction("Rotate", IE_Pressed, this, &UGrabber::RotateStart);
		input->BindAction("Rotate", IE_Released, this, &UGrabber::RotateEnd);
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