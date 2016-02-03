#include "Model_3D.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

#define ARM_DEBUG

Model_3D::Model_3D()
{
	commands = new bool[(int)COMMANDS::NUM_COMMANDS] {false};

	for (auto iter : all_camera_movement)
		camera_movement[iter] = false;

	for (auto iter : all_camera_rotation)
		camera_rotation[iter] = 0.f;

	m_worldNode = new SceneNode();

	m_spatialPartition = new SpatialPartition(m_worldNode, 10, 10);
}

Model_3D::~Model_3D()
{
}

static Mesh *mesh;
static Object *object;
static SceneNode *node;

void Model_3D::Init()
{
}

std::map<Model_3D::CAMERA_MOVEMENT, void (Camera3::*)(float)> func_camera_movement = {
	{ Model_3D::CAMERA_MOVEMENT::MOVE_FORWARD, &Camera3::MoveForward },
	{ Model_3D::CAMERA_MOVEMENT::MOVE_BACKWARD, &Camera3::MoveBackward },
	{ Model_3D::CAMERA_MOVEMENT::MOVE_LEFT, &Camera3::MoveLeft },
	{ Model_3D::CAMERA_MOVEMENT::MOVE_RIGHT, &Camera3::MoveRight }
};
std::map<Model_3D::CAMERA_ROTATION, void (Camera3::*)(float)> func_camera_rotation = {
	{ Model_3D::CAMERA_ROTATION::ROTATE_UP, &Camera3::LookUp },
	{ Model_3D::CAMERA_ROTATION::ROTATE_LEFT, &Camera3::LookLeft }
};

void Model_3D::Update(double dt)
{
	UpdateCameraMovement(dt);
	UpdateCameraRotation(dt);

	for (auto iter : all_camera_movement)
		camera_movement.at(iter) = false;

	for (auto iter : all_camera_rotation)
		camera_rotation.at(iter) = 0.f;
}

void Model_3D::SetCommands(int command)
{
	commands[command] = true;
}

void Model_3D::UpdateCameraMovement(double dt)
{
	//Camera Movement
	for (auto iter : all_camera_movement)
	if (camera_movement.at(iter))
		(camera.*(func_camera_movement.at(iter)))(dt);
}

void Model_3D::UpdateCameraRotation(double dt)
{
	//Camera Rotation
	for (auto iter : all_camera_rotation)
		(camera.*(func_camera_rotation.at(iter)))(camera_rotation.at(iter) * 0.1f);
}