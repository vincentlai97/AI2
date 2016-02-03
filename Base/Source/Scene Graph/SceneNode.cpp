#include "SceneNode.h"

SceneNode::SceneNode()
: mesh(nullptr)
, transform(glm::mat4(1.f))
, OBB()
, Node()
{
}

SceneNode::~SceneNode()
{
}

OrientedBoundingBox SceneNode::GetTransformedOBB(SceneNode *root)
{
	glm::mat4 transform = this->transform;
	SceneNode *current = dynamic_cast<SceneNode*>(this->parent);

	while (current != root)
	{
		transform = current->transform * transform;
		current = dynamic_cast<SceneNode*>(current->parent);
	}

	OrientedBoundingBox OBB = this->OBB;
	//OBB.SetCentre(glm::vec3(glm::vec4(OBB.GetCentre(), 1) * glm::transpose(transform)));
	OBB.SetCentre(glm::vec3(transform * glm::vec4(OBB.GetCentre(), 1)));
	OBB.SetFrontAxis(glm::vec3(transform * glm::vec4(OBB.GetFrontAxis(), 0)));
	OBB.SetUpAxis(glm::vec3(transform * glm::vec4(OBB.GetUpAxis(), 0)));
	return OBB;
}