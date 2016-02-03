#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::AddProjectile(Projectile projectile)
{
	m_projectileList.push_back(projectile);
}

void ProjectileManager::Update(double dt)
{
	for (auto iter = m_projectileList.begin(); iter != m_projectileList.end(); )
	{
		if ((*iter).m_lifespan < 1000)
			(*iter).Update(dt);
		if ((*iter).m_lifespan < 0.f)
			iter = m_projectileList.erase(iter);
		else ++iter;
	}
}