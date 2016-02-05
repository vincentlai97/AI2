#include "MyView.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

#define VIEW_DIMENSIONS 2

MyView::MyView(Model *model) : View(model)
{
}

MyView::~MyView()
{
}

void MyView::RenderCharacter(Character *character)
{
	static Mesh* healthbar = MeshBuilder::GenerateQuad("hpbar", Color(0, 1, 0), 1.f);
	static Mesh* healthbar2 = MeshBuilder::GenerateQuad("hpbar", Color(1, 0, 0), 1.f);

	modelStack.push(modelStack.top()); {
		modelStack.top() *= character->object->translation;

		RenderMesh(character->object->mesh, false);

		modelStack.top() *= glm::translate<float>(0, 1, 0);
		modelStack.push(modelStack.top()); {
			modelStack.top() *= glm::scale(character->hp / 20.f, 0.5f, 1.f);

			RenderMesh(healthbar, false);
		} modelStack.pop();
		modelStack.top() *= glm::scale(2.5f + character->stats[Character::STR] / 40.f, 0.5f, 1.f);

		RenderMesh(healthbar2, false);
	} modelStack.pop();
}

#define camera m_model->getCamera()

void MyView::Render()
{
#if VIEW_DIMENSIONS == 2
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	projectionStack.push(glm::ortho(-(float)windowWidth / 20, (float)windowWidth / 20, -(float)windowHeight / 20, (float)windowHeight / 20, -1000.f, 1000.f));
	viewStack.push(glm::mat4(1.f));
#else if VIEW_DIMENSIONS == 3
	projectionStack.push(glm::perspective(45.f, 4.f / 3.f, .1f, 10000.f));
	viewStack.push(glm::lookAt(
		glm::vec3(camera.position.x, camera.position.y, camera.position.z),
		glm::vec3(camera.target.x, camera.target.y, camera.target.z),
		glm::vec3(camera.up.x, camera.up.y, camera.up.z)
		));
#endif
	modelStack.push(glm::mat4(1.f));

	static Mesh* mesh = MeshBuilder::GenerateText("text", 16, 16);
	int count = 0;
	for (count; count < 1; ++count)
		mesh->textureID[0] = LoadTGA("Image/arrow.tga");

	GeometryPass();

	MyModel *model = dynamic_cast<MyModel *>(m_model);

	for (Character *iter : model->getHeroes())
		RenderCharacter(iter);
	for (Character *iter : model->getMonsters())
		RenderCharacter(iter);

	for (int count = 0; count < 3; ++count)
	if (model->getmsgs().msgboard[count])
		RenderTextOnScreen(mesh, model->getmsgs().msgs.at(count), Color(1, 0, 0), 30, 0, 30 * count);

	//RenderObjectList(m_model->getObjectList());
	//RenderWorldSceneNode(m_model->getWorldNode());

	LightPass();

	projectionStack.pop();
	viewStack.pop();
	modelStack.pop();
}

#undef camera