#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Update(double dt)
{
	m_position += glm::normalize(m_direction) * m_speed * (float)dt;
	m_length = m_speed * dt;
	m_lifespan -= dt;
}