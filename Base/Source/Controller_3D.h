#pragma once

#include "Controller.h"

#include "Model_3D.h"

class Controller_3D : public Controller
{
public:
	Controller_3D(Model* model, View* view) : Controller(model, view) {}
	~Controller_3D();

	virtual void Init();

protected:
	virtual void Update();

};

#define CAMERA_MOVEMENT_TYPE WASD
#define CAMERA_ROTATION_TYPE MOUSE