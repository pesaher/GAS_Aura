// Copyright pesaher

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UAuraOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParameters;

/**
 *
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UAuraOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParameters& InWidgetControllerParameters);

	void InitOverlay(const FWidgetControllerParameters& WidgetControllerParameters);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlayWidgetController> OverlayWidgetControllerClass;

private:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY()
	TObjectPtr<UAuraOverlayWidgetController> OverlayWidgetController;
};
