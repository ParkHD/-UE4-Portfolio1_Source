// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentActor.generated.h"

// ¿Â∫ÒActor
UCLASS()
class LADYBUG_API AEquipmentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* SkeletalMesh;
//protected:
//	UPROPERTY(BlueprintReadOnly, EditAnywhere)
//		class UDataTable* itemTable;
//	UPROPERTY(EditAnywhere)
//		FName itemCode;
public:
	//template<typename T>
	//const T* GetItemInfo();

	class USkeletalMeshComponent* GetSkeletalMesh() { return SkeletalMesh; }
};

//template<typename T>
//inline const T* AEquipmentActor::GetItemInfo()
//{
//	if (itemTable != nullptr)
//	{
//		return itemTable->FindRow<T>(itemCode, "");
//	}
//	return nullptr;
//}