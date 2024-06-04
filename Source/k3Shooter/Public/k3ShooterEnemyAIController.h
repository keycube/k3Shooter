// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "k3ShooterEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class K3SHOOTER_API Ak3ShooterEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	Ak3ShooterEnemyAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

    UPROPERTY(Transient)
    UBehaviorTreeComponent* BehaviorTreeComponent;
	
	UPROPERTY(Transient)
    class UBlackboardComponent* BlackboardComponent;
};
