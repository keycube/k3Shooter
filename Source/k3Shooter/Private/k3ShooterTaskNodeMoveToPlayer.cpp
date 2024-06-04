// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterTaskNodeMoveToPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "k3ShooterEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type Uk3ShooterTaskNodeMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Player"), Cast<Ak3ShooterEnemyBase>(OwnerComp.GetAIOwner()->GetPawn())->GetPlayer()->GetActorLocation());
    return EBTNodeResult::Succeeded;
}
