// Copyright pesaher

#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParameters(const FWidgetControllerParameters& InWidgetControllerParameters)
{
	PlayerController = InWidgetControllerParameters.PlayerController;
	PlayerState = InWidgetControllerParameters.PlayerState;
	AbilitySystemComponent = InWidgetControllerParameters.AbilitySystemComponent;
	AttributeSet = InWidgetControllerParameters.AttributeSet;
}
