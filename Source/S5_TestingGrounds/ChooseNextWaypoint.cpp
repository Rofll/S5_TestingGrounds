// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	APawn* contolledPawn = aiController->GetPawn();
	APatrollingGuard* patrollingGuard = Cast<APatrollingGuard>(contolledPawn);
	TArray<AActor*> patrollingPoints = patrollingGuard->patrolPointsCPP;

	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();

	int32 index = blackboardComp->GetValueAsInt(indexKey.SelectedKeyName);

	blackboardComp->SetValueAsObject(waypointKey.SelectedKeyName, patrollingPoints[index]);

	index++;

	index = index % patrollingPoints.Num();

	blackboardComp->SetValueAsInt(indexKey.SelectedKeyName, index);


	return EBTNodeResult::Succeeded;
}

