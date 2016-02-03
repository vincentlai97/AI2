#include "OrientedBoundingBox.h"

OrientedBoundingBox::OrientedBoundingBox(glm::vec3 centre, glm::vec3 frontAxis, glm::vec3 upAxis, float front_min, float front_max, float up_min, float up_max, float right_min, float right_max) :
	m_centre(centre),
	m_frontAxis(frontAxis),
	m_upAxis(upAxis),
	m_lengths()
{
	m_lengths[FRONT_AXIS][MIN_LENGTH] = front_min;
	m_lengths[FRONT_AXIS][MAX_LENGTH] = front_max;
	m_lengths[UP_AXIS][MIN_LENGTH] = up_min;
	m_lengths[UP_AXIS][MAX_LENGTH] = up_max;
	m_lengths[RIGHT_AXIS][MIN_LENGTH] = right_min;
	m_lengths[RIGHT_AXIS][MAX_LENGTH] = right_max;
}

OrientedBoundingBox::OrientedBoundingBox(glm::vec3 centre, glm::vec3 frontAxis, glm::vec3 upAxis, std::array<std::array<float, 2>, 3> lengths) :
	m_centre(centre),
	m_frontAxis(frontAxis),
	m_upAxis(upAxis),
	m_lengths(lengths)
{
}

OrientedBoundingBox::~OrientedBoundingBox()
{
}

bool OrientedBoundingBox::CheckCollision(const OrientedBoundingBox &other) const
{
	for (int count = 0; count < 3; ++count)
	{
		if (!this->CheckCollision(other, GetAxis(count))) return false;
		if (!this->CheckCollision(other, other.GetAxis(count))) return false;
		for (int count2 = 0; count2 < 3; ++count2)
		if (!this->CheckCollision(other, glm::cross(GetAxis(count), other.GetAxis(count2)))) return false;
	}
	return true;
}

bool OrientedBoundingBox::CheckCollision(const OrientedBoundingBox &other, glm::vec3 axis) const
{
	if (axis == glm::vec3(0))
		return true;
	axis = glm::normalize(axis);

	float thisMin = glm::dot(this->m_centre, axis);
	float thisMax = glm::dot(this->m_centre, axis);
	float otherMin = glm::dot(other.m_centre, axis);
	float otherMax = glm::dot(other.m_centre, axis);
	float temp;

	for (int frontcount = MIN_LENGTH; frontcount <= MAX_LENGTH; ++frontcount)
	for (int upcount = MIN_LENGTH; upcount <= MAX_LENGTH; ++upcount)
	for (int rightcount = MIN_LENGTH; rightcount <= MAX_LENGTH; ++rightcount)
	{
		temp = glm::dot(this->m_centre + m_frontAxis * m_lengths[FRONT_AXIS][frontcount] + m_upAxis * m_lengths[UP_AXIS][upcount] + GetRightAxis() * m_lengths[RIGHT_AXIS][rightcount], axis);
		thisMin = (thisMin < temp) ? thisMin : temp;
		thisMax = (thisMax > temp) ? thisMax : temp;
		temp = glm::dot(other.m_centre + other.m_frontAxis * other.m_lengths[FRONT_AXIS][frontcount] + other.m_upAxis * other.m_lengths[UP_AXIS][upcount] + other.GetRightAxis() * other.m_lengths[RIGHT_AXIS][rightcount], axis);
		otherMin = (otherMin < temp) ? otherMin : temp;
		otherMax = (otherMax > temp) ? otherMax : temp;
	}

	float span = (thisMax > otherMax ? thisMax : otherMax) - (thisMin < otherMin ? thisMin : otherMin);
	float length = (thisMax - thisMin) + (otherMax - otherMin);
	return !(span > length);
}