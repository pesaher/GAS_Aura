// Copyright pesaher

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/AuraHighlightInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase, public IAuraHighlightInterface
{
	GENERATED_BODY()

public:
	AAuraEnemyCharacter();
	
	virtual void SetActorHighlight_Implementation(bool bActivateHighlight) override;
};
