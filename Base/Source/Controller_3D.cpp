#include "Controller_3D.h"

//TEMP
#include "MyModel.h"

Controller_3D::~Controller_3D()
{
}

void Controller_3D::Init()
{
	Controller::Init();

	glfwSetInputMode(view->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Controller_3D::Update()
{
	Model_3D *model = dynamic_cast<Model_3D*>(this->model);

#if CAMERA_MOVEMENT_TYPE == WASD
	if (IsKeyPressed('W')) model->SetCommands(Model_3D::CAMERA_MOVEMENT::MOVE_FORWARD);
	if (IsKeyPressed('S')) model->SetCommands(Model_3D::CAMERA_MOVEMENT::MOVE_BACKWARD);
	if (IsKeyPressed('A')) model->SetCommands(Model_3D::CAMERA_MOVEMENT::MOVE_LEFT);
	if (IsKeyPressed('D')) model->SetCommands(Model_3D::CAMERA_MOVEMENT::MOVE_RIGHT);
#endif

#if CAMERA_ROTATION_TYPE == MOUSE
	double mouseX, mouseY;
	glfwGetCursorPos(view->getWindow(), &mouseX, &mouseY);
	model->SetCommands(Model_3D::CAMERA_ROTATION::ROTATE_UP, mouseY);
	model->SetCommands(Model_3D::CAMERA_ROTATION::ROTATE_LEFT, mouseX);
	glfwSetCursorPos(view->getWindow(), 0, 0);
#endif

	//TEMP
	MyModel *mymodel = dynamic_cast<MyModel*>(this->model);
	mymodel->SetCommands(MyModel::WEAPON_COMMANDS::SHOOT, glfwGetMouseButton(view->getWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);

	Controller::Update();
}