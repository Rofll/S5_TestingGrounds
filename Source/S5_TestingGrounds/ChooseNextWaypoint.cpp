// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <PatrolRouteComponent.h>

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	AAIController* aiController = OwnerComp.GetAIOwner();
	APawn* controlledPawn = aiController->GetPawn();
	UPatrolRouteComponent* patrolRouteComponent = controlledPawn->FindComponentByClass<UPatrolRouteComponent>();
	
	if (!ensure(patrolRouteComponent))
	{
		return EBTNodeResult::Failed;
	}

	TArray<AActor*> patrollingPoints = patrolRouteComponent->GetPatrolPoints();

	if (patrollingPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No patrol points"));
		return EBTNodeResult::Failed;
	}

	
	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();

	int32 index = blackboardComp->GetValueAsInt(indexKey.SelectedKeyName);

	blackboardComp->SetValueAsObject(waypointKey.SelectedKeyName, patrollingPoints[index]);

	index++;

	index = index % patrollingPoints.Num();

	blackboardComp->SetValueAsInt(indexKey.SelectedKeyName, index);


	return EBTNodeResult::Succeeded;
}

