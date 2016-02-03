#include "SpatialPartitionGrid.h"

#include <algorithm>

SpatialPartitionGrid::SpatialPartitionGrid()
{
}

SpatialPartitionGrid::~SpatialPartitionGrid()
{
}

void SpatialPartitionGrid::AddSceneNode(SceneNode* sceneNode)
{
	if (std::find(m_list.begin(), m_list.end(), sceneNode) != m_list.end()) return;

	m_list.push_back(sceneNode);
}

void SpatialPartitionGrid::RemoveSceneNode(SceneNode* sceneNode)
{
	if (std::find(m_list.begin(), m_list.end(), sceneNode) == m_list.end()) return;

	m_list.erase(std::find(m_list.begin(), m_list.end(), sceneNode));
}