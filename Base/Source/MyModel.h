#ifndef MY_MODEL_H
#define MY_MODEL_H

#include "Model_3D.h"

#include "Projectile\ProjectileManager.h"

class MyModel : public Model_3D
{
public:
	enum class WEAPON_COMMANDS
	{
		SHOOT,
	};

	MyModel();
	~MyModel();

	virtual void Init();
	virtual void Update(double dt);

	virtual void SetCommands(WEAPON_COMMANDS command, bool _bool = true) { weapon_commands.at(command) = _bool; }

	virtual ProjectileManager GetProjectileManager() { return m_projectileManager; }

private:
	std::map<WEAPON_COMMANDS, bool> weapon_commands;

	ProjectileManager m_projectileManager;

};

#define NUM_WEAPON_COMMANDS 1U
const std::array<MyModel::WEAPON_COMMANDS, NUM_WEAPON_COMMANDS> all_weapon_commands = {
	MyModel::WEAPON_COMMANDS::SHOOT
};

#endif