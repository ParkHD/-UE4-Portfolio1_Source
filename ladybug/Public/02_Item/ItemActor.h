// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "02_Item/ItemTypes.h"
#include "02_Item/Item.h"

#include "ItemActor.generated.h"

// 사용 안함
// 아이템 Actor -> 몬스터 죽으면 아이템 드랍에서 전투 종료 후 전리품 관리로 변경 
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
		class UWidgetComponent* pickUpWidgetComponent;				// 아이템 픽업 위젯

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UDataTable* itemTable;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName itemCode;							// 아이템 구분할 고유 코드
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float itemCount;						// 아이템 개수

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class UItem> ItemClass;		// 아이템class
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

