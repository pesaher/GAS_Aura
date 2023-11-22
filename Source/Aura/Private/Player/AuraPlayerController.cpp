// Copyright pesaher

#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/AuraHighlightInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	CurrentHighlightedActor = nullptr;

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (CursorHit.bBlockingHit)
	{
		IAuraHighlightInterface* LastHighlightedActor = CurrentHighlightedActor;
		CurrentHighlightedActor = Cast<IAuraHighlightInterface>(CursorHit.GetActor());
		if (LastHighlightedActor != CurrentHighlightedActor)
		{
			if (LastHighlightedActor)
			{
				IAuraHighlightInterface::Execute_SetActorHighlight(Cast<UObject>(LastHighlightedActor), false);
			}
			if (CurrentHighlightedActor)
			{
				IAuraHighlightInterface::Execute_SetActorHighlight(CursorHit.GetActor(), true);
			}
		}
	}
}
