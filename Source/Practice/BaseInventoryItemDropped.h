// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryItem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BaseInventoryItemDropped.generated.h"

UCLASS()
class PRACTICE_API ABaseInventoryItemDropped : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	UBoxComponent* BoxCollision;

	UPROPERTY()
	UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	ABaseInventoryItemDropped();

	ABaseInventoryItemDropped(ABaseInventoryItem* OwnerItem);

	UFUNCTION(Server, Unreliable, WithValidation)
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
											 const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	ABaseInventoryItem* Item;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
