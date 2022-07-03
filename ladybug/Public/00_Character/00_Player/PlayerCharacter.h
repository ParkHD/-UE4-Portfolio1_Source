// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override; 
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnConstruction(const FTransform& Transform)override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UInventoryComponent* InventoryComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UEquipmentComponent* EquipmentComponent;

public:
	class UCameraComponent* GetCameraComponent() { return Camera; }
	class UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; }
#pragma region SkeletalMesh
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* HeadMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* HelmetMeshComponent1;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* UpperBodyMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ArmorMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ArmorMeshComponent2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ArmorMeshComponent3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* CapeMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ShoulderMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* HandMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* GloveMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* GloveMeshComponent2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* GloveMeshComponent3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* LowerBodyMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* PantsMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* PantsMeshComponent2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* PantsMeshComponent3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* FootMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ShoesMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ShoesMeshComponent2;
public:
	class USkeletalMeshComponent* GetHelmetMesh() { return HelmetMeshComponent1; }
	class USkeletalMeshComponent* GetClothMesh() { return ArmorMeshComponent1; }
	class USkeletalMeshComponent* GetCapeMesh() { return CapeMeshComponent; }

#pragma endregion

	
protected:
	UPROPERTY()
		float moveDirection;
	
public:
	bool bInputComboAttack = false;
	bool isBlockPressed = false;
	bool isAttackPressed = false;
	bool isAimming = false;
	bool isInteract = false;
protected:
	UPROPERTY(EditAnywhere)
		FVector originSpringArmTargetOffset = FVector(0, 0, 100);
	UPROPERTY(EditAnywhere)
		float originArmlength = 500.f;
	UPROPERTY(EditAnywhere)
		float interpSpeed;
	
public:
	UPROPERTY(VisibleAnywhere)
		TArray<class AItemActor*> pickUpAbleItems;
	UPROPERTY(VisibleAnywhere)
		class AActor* interactAbleTarget;
private:
	void MoveForward(float newAxisValue);
	void MoveRight(float newAxisValue);
	void LookUp(float newAxisValue);
	void Turn(float newAxisValue);
	virtual void Jump() override;
	void PressRun();
	void ReleaseRun();

	void PressBlock();
	void ReleaseBlock();

	// 아이템 줍기
	void PickUp();

	void PressAttack();
	void ReleaseAttack();

	void PressSkill1();
	void PressSkill2();

	void PressInteract();

	void PressOption();
	void SawpWeapon(float newAxisValue);
public:
	// 캐릭터 이동방향 구하기
	float GetMoveDirection();
	void SetAttackMontage(class UAnimMontage* montage);
	void SetHitMontage(class UAnimMontage* montage);

	void SetInteract(bool binteract) { isInteract = binteract; }


public:
	void SetCharacter(class AWorldBaseCharacter* WorldCharacter);
};
