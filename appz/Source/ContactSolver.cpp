#include "ContactSolver.h"

ContactSolver::ContactSolver()
{
}

ContactSolver::~ContactSolver()
{
}

bool ContactSolver::CheckThisCollision(Voxel* voxel1, Voxel* voxel2, const double deltaTime)
{
	Voxel tempVox1 = *voxel1;
	Voxel tempVox2 = *voxel2;
	const double numOfSteps = 1000;
	const double timestep = 0.001;
	double timeOfImpact = 0.0;
	while(!tempVox1.IsCollidingWith(tempVox2) && timeOfImpact < deltaTime)
	{
		tempVox1.UpdateTo(timestep);
		tempVox2.UpdateTo(timestep);
		timeOfImpact += timestep;
	}
	//if collision is found
	if(timeOfImpact < deltaTime)
	{
		list.InsertNode(Contact(voxel1, voxel2, timeOfImpact));
		return true;
	}
	return false;
}

void ContactSolver::ResolveAllCollisionsAccordingTo(const double deltaTime)
{
	while(!list.IsEmpty())
	{
		if(list[0].IsStillValid())
		{
			list[0].ResolveAccordingTo(deltaTime);
		}
		list.DeleteNode(0);
	}
}