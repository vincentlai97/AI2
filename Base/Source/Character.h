#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

#include <array>
#include <vector>

enum class ROLE
{
	KNIGHT,
	ARCHER,
	HEALER,
	MONSTER
};

enum class STATE
{
	KNIGHT_MOVE = 0,
	KNIGHT_ATTACK,
	ARCHER_MOVE = 0,
	ARCHER_ATTACK,
	HEALER_MOVE = 0,
	HEALER_HEAL,
	MONSTER_MOVE = 0,
	MONSTER_ATTACK,
};

class Character
{
public:
	Object *object;
	int hp;
	std::array<int, 3> stats;
	ROLE role;
	STATE state;
	Character *target;

	virtual void UpdateState(std::array<Character *, 3> heroes, std::vector<Character *> monsters);
	virtual void Update();

	glm::vec3 getPos()
	{
		return glm::vec3(object->translation[3][0], object->translation[3][1], object->translation[3][2]);
	}
};

#endif