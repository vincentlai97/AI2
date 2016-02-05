#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

#include <array>
#include <vector>
#include <map>

#include <iostream>

#include "MsgBoard.h"

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
		KNIGHT_IDLE = 0,
		KNIGHT_MOVE,
		KNIGHT_ATTACK,
		KNIGHT_PROTECT,
		ARCHER_IDLE = 0,
		ARCHER_MOVE,
		ARCHER_ATTACK,
		ARCHER_RETREAT,
		HEALER_IDLE = 0,
		HEALER_MOVE,
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
	bool targetReached;

	Character() : attacked(false), attackBuffer(0), targetReached(true)
	{
		stats.fill(0);
	};

	virtual void UpdateState(std::array<Character *, 3> heroes, std::vector<Character *> monsters, double dt, MsgBoard &msgboard);
	virtual void Update(double dt);

	virtual void Move(glm::vec3 direction, double dt);

	glm::vec3 getPos()
	{
		return glm::vec3(object->translation[3][0], object->translation[3][1], object->translation[3][2]);
	}

	int getMaxHP()
	{
		return 50 + stats[STR] / 2.f;
	}

	void CallForHelp(std::array<Character *, 3> heroes, MsgBoard &msgboard);
	void CallForHeal(std::array<Character *, 3> heroes, MsgBoard &msgboard);
};

#endif