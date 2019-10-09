#include "DepthFirstPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <algorithm>

using namespace std;

DepthFirstPathfinder::DepthFirstPathfinder( Graph* pGraph )
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph) )
{
}

DepthFirstPathfinder::~DepthFirstPathfinder()
{
}

Path DepthFirstPathfinder::findPath( Node* pFrom, Node* pTo )
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	list<Node*> nodesToVisit;
	nodesToVisit.push_front( pFrom );

#ifdef VISUALIZE_PATH
	mPath.clear();
	mVisitedNodes.clear();
	mVisitedNodes.push_back( pFrom );
#endif
	
	Path path;

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while( pCurrentNode != pTo && nodesToVisit.size() > 0 )
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		path.addNode( pCurrentNode );

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections( pCurrentNode->getId() );

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (auto iter : connections)
		{
			Connection* pConnection = iter;
			Node* pTempToNode = iter->getToNode();
			if (!toNodeAdded &&
				!path.containsNode(pTempToNode) &&
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end())
			{
				nodesToVisit.push_front(pTempToNode);//uncomment me for depth-first search
				//nodesToVisit.push_back( pTempToNode );//uncomment me for breadth-first search
				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}
				#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
				#endif
			}
		}
	}
	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mPath = path;
#endif
	return path;

}

