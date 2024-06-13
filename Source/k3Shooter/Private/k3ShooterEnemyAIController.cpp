// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterEnemyAIController.h"
#include "k3ShooterEnemyBase.h"

Ak3ShooterEnemyAIController::Ak3ShooterEnemyAIController(const FObjectInitializer& ObjectInitializer){
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
}

void Ak3ShooterEnemyAIController::OnPossess(APawn* InPawn){

    Super::OnPossess(InPawn);

    if (auto e = Cast<Ak3ShooterEnemyBase>(InPawn)) { // Check if we are possessing the right type of enemy
        if (e->TreeAsset && e->TreeAsset->BlackboardAsset) {
            BlackboardComponent->InitializeBlackboard(*e->TreeAsset->BlackboardAsset);
            BehaviorTreeComponent->StartTree(*e->TreeAsset);
        }
    }
}