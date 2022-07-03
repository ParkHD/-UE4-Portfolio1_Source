// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "02_Item/ItemTypes.h"
#include "02_Item/Item.h"

#include "ItemActor.generated.h"

UCLASS()
class LADYBUG_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:	
	UPROPERTY(EditAnywhere)
		class USphereComponent* sphereComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* particleSystemComponent;
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* pickUpWidgetComponent;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UDataTable* itemTable;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName itemCode;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float itemCount;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UItem> ItemClass;
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UItem* Item;

public:

private:
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
};

