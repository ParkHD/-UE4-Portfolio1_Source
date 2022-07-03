// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "WorldPlayerCharacter.generated.h"

/**
 * Player's WorldCharacter
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
		class UNiagaraComponent* clickNiagaraComponent;	// 클릭 Particle 관리 컴포넌트
public:
	class UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
protected:
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* clickParticle;			// 마우스 클릭시 나올 Particle

	bool bClickRotate = false;		// 카메라 회전 가능한가?	
	UPROPERTY(EditAnywhere)
		float speed = 10.f;			// 카메라 줌 속도
	UPROPERTY(VisibleAnywhere)
		class AWorldPlayerController* playerController;
protected:
	void ReleaseMove();							// 캐릭터 이동
	void PressRotate();							// 카메라 회전 클릭
	void ReleaseRotate();

	void RotateCamera(float newAxisValue);		// 카메라 회전
	void ZoomCamera(float newAxisValue);		// 카메라 줌

	void PressInventoryKey();					// 인벤토리 열기
	void PressArmyManagerKey();					// 부대관리창 열기
protected:
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
public:
	// 저장된 캐릭터 데이터 덮어쓰기
	virtual void SetCharacterData(FSaveCharacterData CharacterData)override;




	// test -> 에디터에서 입력받은 아이템 인벤토리에 넣어놓기
protected:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UItem>> itemListBP;
};
