// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "00_Character/03_NPC/NPCCharacter.h"
#include "VillageWorldActor.generated.h"

USTRUCT(BlueprintType)
struct FVillageInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag village_Tag;
	UPROPERTY(EditAnywhere)
		FString village_Name;
	UPROPERTY(EditAnywhere)
		FString village_Description;
	UPROPERTY(EditAnywhere)
		TArray<FGameplayTag> village_NPCList;
};	
UCLASS()
class LADYBUG_API AVillageWorldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageWorldActor();

protected:
	UPROPERTY(EditAnywhere)
		class USphereComponent* sphereComponent;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* staticMeshComponent;
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* villageNameWidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag Village_Tag;
	UPROPERTY(EditAnywhere)
		FString Village_Name;
public:
	FName GetVillageTagName() { return Village_Tag.GetTagName(); }

};
