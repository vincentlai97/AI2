#include "View_3D.h"

#ifdef RENDEROBB
#include "MeshBuilder.h"
#endif

#include "gtx\transform.hpp"

View_3D::~View_3D()
{
}

void View_3D::RenderWorldSceneNode(SceneNode *node)
{
#ifdef RENDEROBB
Mesh *OBBCentre = MeshBuilder::GenerateSphere("obbcircle", Color(1, 0, 0), 8, 8, 0.1f);
Mesh *OBBFrame = MeshBuilder::GenerateCube("obbframe", Color(1, 0, 0), 1.f);
#endif
	modelStack.push(modelStack.top()); {
		modelStack.top() *= node->GetTransform();
		if (node->GetMesh() != nullptr)
			RenderMesh(node->GetMesh(), false);
#ifdef RENDEROBB
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		modelStack.push(modelStack.top()); {
			modelStack.top() *= glm::translate(node->GetOBB().GetCentre());

			RenderMesh(OBBCentre, false);

			modelStack.top() *= glm::translate<float>(node->GetOBB().GetLengths()[FRONT_AXIS][MIN_LENGTH], node->GetOBB().GetLengths()[UP_AXIS][MIN_LENGTH], node->GetOBB().GetLengths()[RIGHT_AXIS][MIN_LENGTH]);
			modelStack.top() *= glm::scale<float>(node->GetOBB().GetSize());
			modelStack.top() *= glm::translate<float>(0.5, 0.5, 0.5);
			RenderMesh(OBBFrame, false);
		} modelStack.pop();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
#endif
		for (auto iter : node->GetChildNodes())
		{
			RenderWorldSceneNode(dynamic_cast<SceneNode*>(node->GetChildNode(iter.first)));
		}
	} modelStack.pop();
}