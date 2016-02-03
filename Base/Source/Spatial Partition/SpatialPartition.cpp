#include "SpatialPartition.h"

#include <iostream>

SpatialPartition::SpatialPartition(SceneNode *worldSceneNode, float gridSize_x, float gridSize_z) :
m_worldSceneNode(worldSceneNode),
	m_gridSize_x(gridSize_x),
	m_gridSize_z(gridSize_z)
{
}

SpatialPartition::~SpatialPartition()
{
}

void SpatialPartition::AddSceneNode(SceneNode *sceneNode)
{
	OrientedBoundingBox OBB = sceneNode->GetTransformedOBB(m_worldSceneNode);

	float temp;

	float min_x, max_x;
	min_x = max_x = glm::dot(OBB.GetCentre() + OBB.GetFrontAxis() * OBB.GetLengths()[FRONT_AXIS][MIN_LENGTH] + OBB.GetUpAxis() * OBB.GetLengths()[UP_AXIS][MIN_LENGTH] + OBB.GetRightAxis() * OBB.GetLengths()[RIGHT_AXIS][MIN_LENGTH], glm::vec3(1, 0, 0));

	for (int frontcount = MIN_LENGTH; frontcount <= MAX_LENGTH; ++frontcount)
	for (int upcount = MIN_LENGTH; upcount <= MAX_LENGTH; ++upcount)
	for (int rightcount = MIN_LENGTH; rightcount <= MAX_LENGTH; ++rightcount)
	{
		temp = max_x = glm::dot(OBB.GetCentre() + OBB.GetFrontAxis() * OBB.GetLengths()[FRONT_AXIS][frontcount] + OBB.GetUpAxis() * OBB.GetLengths()[UP_AXIS][upcount] + OBB.GetRightAxis() * OBB.GetLengths()[RIGHT_AXIS][rightcount], glm::vec3(1, 0, 0));
		min_x = (min_x < temp) ? min_x : temp;
		max_x = (max_x > temp) ? max_x : temp;
	}

	float min_z, max_z;
	min_z = max_z = glm::dot(OBB.GetCentre() + OBB.GetFrontAxis() * OBB.GetLengths()[FRONT_AXIS][MIN_LENGTH] + OBB.GetUpAxis() * OBB.GetLengths()[UP_AXIS][MIN_LENGTH] + OBB.GetRightAxis() * OBB.GetLengths()[RIGHT_AXIS][MIN_LENGTH], glm::vec3(1, 0, 0));

	for (int frontcount = MIN_LENGTH; frontcount <= MAX_LENGTH; ++frontcount)
	for (int upcount = MIN_LENGTH; upcount <= MAX_LENGTH; ++upcount)
	for (int rightcount = MIN_LENGTH; rightcount <= MAX_LENGTH; ++rightcount)
	{
		temp = max_z = glm::dot(OBB.GetCentre() + OBB.GetFrontAxis() * OBB.GetLengths()[FRONT_AXIS][frontcount] + OBB.GetUpAxis() * OBB.GetLengths()[UP_AXIS][upcount] + OBB.GetRightAxis() * OBB.GetLengths()[RIGHT_AXIS][rightcount], glm::vec3(0, 0, 1));
		min_z = (min_z < temp) ? min_z : temp;
		max_z = (max_z > temp) ? max_z : temp;
	}

	int _min_x = floor(min_x / m_gridSize_x);
	int _max_x = floor(max_x / m_gridSize_x);
	int _min_z = floor(min_z / m_gridSize_z);
	int _max_z = floor(max_z / m_gridSize_z);

	for (int xCount = _min_x; xCount <= _max_x; ++xCount)
	for (int zCount = _min_z; zCount <= _max_z; ++zCount)
		AddSceneNode(sceneNode, std::pair<int, int>(xCount, zCount));
}

void SpatialPartition::AddSceneNode(SceneNode *sceneNode, std::pair<int, int> grid)
{
	m_gridList[grid].AddSceneNode(sceneNode);
}

void SpatialPartition::Update(SceneNode *sceneNode)
{
	for (auto iter : m_gridList)
	{
		iter.second.RemoveSceneNode(sceneNode);
	}
	AddSceneNode(sceneNode);
}