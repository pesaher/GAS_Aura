// Copyright pesaher

#include "UI/WidgetController/AuraWidgetController.h"

#include "Player/AuraPlayerState.h"

void UAuraWidgetController::SetWidgetControllerParameters(AAuraPlayerState* InPlayerState)
{
	PlayerState = InPlayerState;
	PlayerController = PlayerState->GetPlayerController();
	AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
	AttributeSet = PlayerState->GetAttributeSet();

	BindCallbacksToDependencies();
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}

void UAuraWidgetController::BroadcastInitialValues()
{
}
