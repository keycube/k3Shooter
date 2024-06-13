// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "k3ShooterTaskNodeMoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class K3SHOOTER_API Uk3ShooterTaskNodeMoveToPlayer : public UBTTaskNode{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:

	FVector TargetLocation;

};
