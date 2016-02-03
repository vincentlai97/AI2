#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

#include <array>
#include <vector>

class Character
{
public:
	enum class ROLE
	{
		KNIGHT,
		ARCHER,
		HEALER,
		MONSTER
	};

	enum STATS
	{
		STR,
		DEX,
		INT
	};

	enum class STATE
	{
		KNIGHT_MOVE = 0,
		KNIGHT_ATTACK,
		ARCHER_MOVE = 0,
		ARCHER_ATTACK,
		ARCHER_RETREAT,
		HEALER_MOVE = 0,
		HEALER_HEAL,
		HEALER_RETREAT,
		MONSTER_PATROL = 0,
		MONSTER_MOVE,
		MONSTER_ATTACK,
	};

	Object *object;
	int hp;
	std::array<int, 3> stats;
	ROLE role;
	STATE state;
	Character *target;
	float attackBuffer;
	bool attacked;
	Character *attacker;

	Character() : attacked(false), attackBuffer(0)
	{
		stats.fill(0);
	};

	virtual void UpdateState(std::array<Character *, 3> heroes, std::vector<Character *> monsters, double dt);
	virtual void Update(double dt);

	virtual void Move(glm::vec3 direction, double dt);

	glm::vec3 getPos()
	{
		return glm::vec3(object->translation[3][0], object->translation[3][1], object->translation[3][2]);
	}
};

#endif