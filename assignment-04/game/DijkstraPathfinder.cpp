#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <algorithm>

using std::list;

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{}

Path DijkstraPathfinder::findPath(Node * pFrom, Node * pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	// Allocate nodes to visit list and place starting node in it
	list<Node*> nodesToVist;
	nodesToVist.push_front(pFrom);

#ifdef VISUALIZE_PATH
	mPath.clear();
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	Path path;

	Node* pCurrentNode = nullptr;
	bool toNodeAdded = false;




	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");
#ifdef VISUALIZE_PATH
	mPath = path;
#endif

	return mPath;
}
