// Copyright pesaher

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EAuraEffectPolicy
{
	None,
	OnOverlap,
	OnEndOverlap
};

USTRUCT(BlueprintType)
struct FAuraEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAuraEffectPolicy EffectApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAuraEffectPolicy EffectRemovalPolicy;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	bool bDestroyOnEffectRemoval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	FAuraEffect InstantGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	FAuraEffect DurationGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	FAuraEffect InfiniteGameplayEffect;
};
