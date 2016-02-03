#ifndef SCENENODE_H
#define SCENENODE_H

#include "Node.h"

#include "..\Mesh.h"

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc\matrix_transform.hpp"

#include "../OrientedBoundingBox.h"

class SceneNode : public Node
{
public:
	SceneNode();
	~SceneNode();

	void SetMesh(Mesh *mesh) { this->mesh = mesh; }
	Mesh* GetMesh() { return mesh; }

	void SetTransform(const glm::mat4 &transform) { this->transform = transform; }
	glm::mat4 GetTransform() const { return transform; }

	void SetOBB(const OrientedBoundingBox &OBB) { this->OBB = OBB; }
	OrientedBoundingBox GetOBB() const { return OBB; }
	OrientedBoundingBox GetTransformedOBB(SceneNode *root);

	void Translate(const glm::vec3 &translate) { transform *= glm::translate(translate); }
	void Rotate(const float &angle, const glm::vec3 &axes) { transform = glm::rotate(transform, angle, axes); }
	void Scale(const glm::vec3 &scale) { transform = glm::scale(transform, scale); }

	bool CheckCollision(SceneNode *other, SceneNode *root);

private:
	Mesh *mesh;
	glm::mat4 transform;
	OrientedBoundingBox OBB;

};

#endif