#ifndef PROJECTILETOOBB_H
#define PROJECTILETOOBB_H

#include "Projectile.h"
#include "../OrientedBoundingBox.h"

#include "gtx\transform.hpp"

static OrientedBoundingBox ProjectiletoOBB(Projectile projectile)
{
	glm::mat4 transform(1.f);
	transform *= glm::rotate(180 + glm::degrees(glm::atan(projectile.m_direction.x, projectile.m_direction.z)), glm::vec3(0, 1, 0));
	transform *= glm::rotate(glm::degrees(glm::asin(projectile.m_direction.y)), glm::vec3(1, 0, 0));

	OrientedBoundingBox OBB(projectile.m_position, glm::normalize(projectile.m_direction), glm::vec3(transform * glm::vec4(0, 1, 0, 0)), -projectile.m_length, 0, -0.01, 0.01, -0.01, 0.01);

	return OBB;
}

#endif