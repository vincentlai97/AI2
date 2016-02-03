#include "MyView.h"

#include "MyModel.h"

#define VIEW_DIMENSIONS 2

MyView::MyView(Model *model) : View(model)
{
}

MyView::~MyView()
{
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

	GeometryPass();

	RenderObjectList(m_model->getObjectList());
	RenderWorldSceneNode(m_model->getWorldNode());

	LightPass();

	projectionStack.pop();
	viewStack.pop();
	modelStack.pop();
}

#undef camera