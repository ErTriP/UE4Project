// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInventoryItem.generated.h"

UENUM()
enum class EInventoryItemType : uint8
{
	Unknown,
	Weapon,
	Craft,
	Heal,
	Poison,
	Shield,
	MAX
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FName Name;
	
	UPROPERTY(BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(BlueprintReadOnly)
	EInventoryItemType Type;
	
	UPROPERTY(BlueprintReadOnly)
	bool bCanStack;
	
	UPROPERTY(BlueprintReadOnly)
	bool bUseable;
	
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* Texture2D;
	
	UPROPERTY(BlueprintReadOnly)
	UStaticMesh* StaticMesh;
	
	UPROPERTY(BlueprintReadOnly)
	float HealAmount;
	
	UPROPERTY(BlueprintReadOnly)
	float DamageAmount;

	FItemData()
	{
		Name = "Unknown";
		Description = FText::FromString("Unknown");
		Type = EInventoryItemType::Unknown;
		bCanStack = false;
		bUseable = false;
		HealAmount = 0;
		static ConstructorHelpers::FObjectFinder<UTexture2D> DefaultTexture(TEXT("/Game/CraftResourcesIcons/Textures/Tex_bone_01.Tex_bone_01"));
		if (DefaultTexture.Succeeded())
		{
			Texture2D = DefaultTexture.Object;
		}
		static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/ThirdPersonCPP/Meshes/Colt_Python.Colt_Python"));
		if (DefaultMesh.Succeeded())
		{
			StaticMesh = DefaultMesh.Object;
		}
		
		DamageAmount = 0;
	}
};

UCLASS()
class PRACTICE_API ABaseInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInventoryItem();

	UPROPERTY(BlueprintReadOnly)
	FItemData ItemData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	EInventoryItemType InventoryItemType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Use();

	virtual void Drop();

};
