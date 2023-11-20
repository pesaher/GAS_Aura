// Copyright pesaher


#include "Character/AuraEnemyCharacter.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemyCharacter::SetActorHighlight_Implementation(bool bActivateHighlight)
{
}
