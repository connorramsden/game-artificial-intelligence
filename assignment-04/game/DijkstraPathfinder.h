#include "GridPathfinder.h"

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DijkstraPathfinder : public GridPathfinder
{
public:
	DijkstraPathfinder(Graph* pGraph);

	Path findPath(Node* pFrom, Node* pTo); // delete path when finished  w/ pathfinding
};
