#ifndef PROJETILE_MANAGER_H
#define PROJETILE_MANAGER_H

#include "Projectile.h"

#include <vector>

class ProjectileManager 
{
public:
	ProjectileManager();
	~ProjectileManager();

	void AddProjectile(Projectile projectile);
	std::vector<Projectile> GetProjectiles() { return m_projectileList; }

	void Update(double dt);

private:
	friend Projectile;

	std::vector<Projectile> m_projectileList;

};

#endif