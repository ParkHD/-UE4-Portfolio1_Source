// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "WorldPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API AWorldPlayerCharacter : public AWorldBaseCharacter
{
	GENERATED_BODY()
public:
	AWorldPlayerCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* CameraComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UInventoryComponent* InventoryComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Sound)
		class UAudioComponent* AudioComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UNiagaraComponent* clickNiagaraComponent;
public:
	class UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
protected:
	//UPROPERTY(EditAnywhere)
	//	class UParticleSystem* clickParticle;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* clickParticle;
	bool bClickRotate = false;
	UPROPERTY(EditAnywhere)
		float speed = 10.f;
	UPROPERTY(VisibleAnywhere)
		class AWorldPlayerController* playerController;
protected:
	void ReleaseMove();
	void PressRotate();
	void ReleaseRotate();

	void RotateCamera(float newAxisValue);
	void ZoomCamera(float newAxisValue);

	void PressInventoryKey();
	void PressArmyManagerKey();
protected:
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
public:
	virtual void SetCharacterData(FSaveCharacterData CharacterData)override;




	//test
protected:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UItem>> itemListBP;
};
