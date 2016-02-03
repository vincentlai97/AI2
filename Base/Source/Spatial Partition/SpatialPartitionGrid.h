#ifndef SPATIAL_PARTITION_GRID_H
#define SPATIAL_PARTITION_GRID_H

#include "../Scene Graph/SceneNode.h"

#include <vector>

class SpatialPartitionGrid
{
public:
	SpatialPartitionGrid();
	~SpatialPartitionGrid();

	void AddSceneNode(SceneNode* sceneNode);
	void RemoveSceneNode(SceneNode* sceneNode);

private:
	std::vector<SceneNode*> m_list;
};

#endif