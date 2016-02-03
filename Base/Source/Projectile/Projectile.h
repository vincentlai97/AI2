#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "glm.hpp"

class Projectile
{
public:
	Projectile();
	~Projectile();

	void Update(double dt);

//private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	float m_speed;
	float m_width;
	float m_length;
	float m_lifespan;

};

#endif