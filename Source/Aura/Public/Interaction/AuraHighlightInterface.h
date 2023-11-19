// Copyright pesaher

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AuraHighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAuraHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IAuraHighlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetActorHighlight(bool bActivateHighlight) = 0;
};
