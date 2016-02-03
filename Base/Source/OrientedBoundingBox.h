#ifndef ORIENTEDBOUNDINGBOX_H
#define ORIENTEDBOUNDINGBOX_H

#include "glm.hpp"

#include <array>

#define FRONT_AXIS 0
#define UP_AXIS 1
#define RIGHT_AXIS 2

#define MIN_LENGTH 0
#define MAX_LENGTH 1

class OrientedBoundingBox
{
public:
	OrientedBoundingBox(glm::vec3 centre = glm::vec3(), glm::vec3 frontAxis = glm::vec3(), glm::vec3 upAxis = glm::vec3(), float front_min = 0, float front_max = 0, float up_min = 0, float up_max = 0, float right_min = 0, float right_max = 0);
	OrientedBoundingBox(glm::vec3 centre, glm::vec3 frontAxis, glm::vec3 upAxis, std::array<std::array<float, 2>, 3> lengths);
	~OrientedBoundingBox();

	void SetCentre(const glm::vec3 &centre) { m_centre = centre; }
	glm::vec3 GetCentre() const { return m_centre; }

	void SetFrontAxis(const glm::vec3 &frontAxis) { m_frontAxis = frontAxis; }
	glm::vec3 GetFrontAxis() const { return m_frontAxis; }

	void SetUpAxis(const glm::vec3 &upAxis) { m_upAxis = upAxis; }
	glm::vec3 GetUpAxis() const { return m_upAxis; }

	glm::vec3 GetRightAxis() const { return glm::cross(m_frontAxis, m_upAxis); }

	void SetLengths(const std::array<std::array<float, 2>, 3> &lengths) { m_lengths = lengths; }
	std::array<std::array<float, 2>, 3> GetLengths() { return m_lengths; }

	glm::vec3 GetSize() { return glm::vec3(-m_lengths[FRONT_AXIS][MIN_LENGTH] + m_lengths[FRONT_AXIS][MAX_LENGTH], -m_lengths[UP_AXIS][MIN_LENGTH] + m_lengths[UP_AXIS][MAX_LENGTH], -m_lengths[RIGHT_AXIS][MIN_LENGTH] + m_lengths[RIGHT_AXIS][MAX_LENGTH]); }

	bool CheckCollision(const OrientedBoundingBox &other) const;

private:
	glm::vec3 m_centre;

	glm::vec3 m_frontAxis;
	glm::vec3 m_upAxis;

	std::array<std::array<float, 2>, 3> m_lengths;

	glm::vec3 GetAxis(int axis) const { return (axis == FRONT_AXIS) ? m_frontAxis : (axis == UP_AXIS) ? m_upAxis : (axis == RIGHT_AXIS) ? GetRightAxis() : (throw std::exception()); }

	bool CheckCollision(const OrientedBoundingBox &other, glm::vec3 axis) const;
};

#endif