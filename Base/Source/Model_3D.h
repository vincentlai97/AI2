#ifndef MODEL_3D_H
#define MODEL_3D_H

#include "Model.h"

#include "Spatial Partition\SpatialPartition.h"

#include <array>
#include <map>

class Model_3D : public Model
{
public:
	enum class CAMERA_MOVEMENT
	{
		MOVE_FORWARD,
		MOVE_BACKWARD,
		MOVE_LEFT,
		MOVE_RIGHT,
		NUM_COMMANDS,
	};

	enum class CAMERA_ROTATION
	{
		ROTATE_UP,
		ROTATE_LEFT,
	};

	Model_3D();
	~Model_3D();

	virtual void Init();
	virtual void Update(double dt);
	virtual void SetCommands(int command);
	virtual void SetCommands(CAMERA_MOVEMENT command, bool _bool = true) { camera_movement.at(command) = _bool; }
	virtual void SetCommands(CAMERA_ROTATION command, float angle) { camera_rotation.at(command) = angle; }

protected:
	std::map<CAMERA_MOVEMENT, bool> camera_movement;
	std::map<CAMERA_ROTATION, float> camera_rotation;

	SpatialPartition *m_spatialPartition;

	virtual void UpdateCameraMovement(double dt);
	virtual void UpdateCameraRotation(double dt);
};

#define NUM_CAMERA_MOVEMENT 4U
const std::array<Model_3D::CAMERA_MOVEMENT, NUM_CAMERA_MOVEMENT> all_camera_movement = {
	Model_3D::CAMERA_MOVEMENT::MOVE_FORWARD,
	Model_3D::CAMERA_MOVEMENT::MOVE_BACKWARD,
	Model_3D::CAMERA_MOVEMENT::MOVE_LEFT,
	Model_3D::CAMERA_MOVEMENT::MOVE_RIGHT
};

#define NUM_CAMERA_ROTATION 2U
const std::array<Model_3D::CAMERA_ROTATION, NUM_CAMERA_ROTATION> all_camera_rotation = {
	Model_3D::CAMERA_ROTATION::ROTATE_UP,
	Model_3D::CAMERA_ROTATION::ROTATE_LEFT,
};

#endif