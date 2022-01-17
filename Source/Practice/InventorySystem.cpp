// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}


void UInventorySystem::OnRep_Slots()
{
	UpdateInventorySlots();
}

void UInventorySystem::UpdateInventorySlots()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "I take item");
}

// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventorySystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UInventorySystem, Slots, COND_OwnerOnly);
}


// Called every frame
void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventorySystem::RemoveSlot_Implementation(int32 Index)
{
	Slots.RemoveAt(Index);
}

void UInventorySystem::AddSlot_Implementation(ABaseInventoryItem* item)
{
	Slots.Add(item);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "SomeActor takes inventory item");
	UpdateInventorySlots();
	OnAddedItem.Broadcast(item);
}

