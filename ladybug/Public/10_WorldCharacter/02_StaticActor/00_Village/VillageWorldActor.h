// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "00_Character/03_NPC/NPCCharacter.h"
#include "VillageWorldActor.generated.h"

// 마을 정보 구조체
USTRUCT(BlueprintType)
struct FVillageInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag village_Tag;
	UPROPERTY(EditAnywhere)
		FString village_Name;					// 마을 이름
	UPROPERTY(EditAnywhere)
		FString village_Description;			// 마을 설명
	UPROPERTY(EditAnywhere)
		TArray<FGameplayTag> village_NPCList;	// 마을에 있는 NPC들
};

// WorldLevel에 배치 할 마을 Actor
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
		class UWidgetComponent* villageNameWidgetComponent;		// 마을 이름 위젯

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
		FString Village_Name;				// 마을 이름
public:
	FName GetVillageTagName() { return Village_Tag.GetTagName(); }

};
