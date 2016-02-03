#ifndef SPATIAL_PARTITION_H
#define SPATIAL_PARTITION_H

#include "SpatialPartitionGrid.h"

#include <map>

class SpatialPartition
{
public:
	SpatialPartition(SceneNode *worldSceneNode, float gridSize_x, float gridSize_z);
	~SpatialPartition();

	void AddSceneNode(SceneNode *sceneNode);

	void Update();
	void Update(SceneNode *sceneNode);

private:
	std::map<std::pair<int, int>, SpatialPartitionGrid> m_gridList;

	SceneNode *m_worldSceneNode;
	float m_gridSize_x, m_gridSize_z;

	void AddSceneNode(SceneNode *sceneNode, std::pair<int, int> grid);
};

#endif