#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"
#include "Path.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent( GridPathfinder* pPathfinder )
	:mpPathfinder(pPathfinder)
{
}

string PathfindingDebugContent::getDebugString()
{
	stringstream theStream;

#ifdef VISUALIZE_PATH
	if( mpPathfinder->mPath.getNumNodes() > 0 )
	{
		theStream << "Pathlength:"<< mpPathfinder->mPath.getNumNodes();
	}
	
	theStream << "  Num Nodes Processed:" << mpPathfinder->mVisitedNodes.size();
#endif
	theStream << "  Elapsed Time:" << mpPathfinder->mTimeElapsed;
	return theStream.str();
}

