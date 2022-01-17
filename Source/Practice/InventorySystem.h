// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddedItem, ABaseInventoryItem*, Item);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystem();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Slots)
	TArray<ABaseInventoryItem*> Slots;

	UFUNCTION()
	void OnRep_Slots();

	UPROPERTY(BlueprintAssignable)
	FOnAddedItem OnAddedItem;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateInventorySlots();
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Unreliable)
	void AddSlot(ABaseInventoryItem* item);

	UFUNCTION(Server, Unreliable)
	void RemoveSlot(int32 Index);
		
};
