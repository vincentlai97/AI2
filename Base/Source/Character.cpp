#include "Character.h"

#include "gtx\transform.hpp"

void Character::UpdateState(std::array<Character *, 3> heroes, std::vector<Character *> monsters)
{
	float monsterDist = glm::distance(getPos(), monsters[0]->getPos());
	switch (role)
	{
	case ROLE::KNIGHT:
		if (2 < monsterDist && monsterDist < 15)
		{
			state = STATE::KNIGHT_MOVE;
			target = monsters[0];
		}
		else
			state = STATE::KNIGHT_ATTACK;
		break;
	case ROLE::ARCHER:
		if (glm::distance(getPos(), monsters[0]->getPos()) > 10)
		{
			state = STATE::ARCHER_MOVE;
			target = monsters[0];
		}
		else
			state = STATE::ARCHER_ATTACK;
		break;
	case ROLE::HEALER:
		Character *knight;
		for (int count = 0; count < 3; ++count)
		{
			if (heroes[count]->role == ROLE::KNIGHT) knight = heroes[count];
		}
		if (glm::distance(getPos(), knight->getPos()) > 5)
		{
			state = STATE::HEALER_MOVE;
			target = knight;
		}
		else
			state = STATE::HEALER_HEAL;
		break;
	case ROLE::MONSTER:
	{
					Character closestHero;
					float dist = 0;
					for (int count = 0; count < 3; ++count)
					{
						if (glm::distance(getPos(), heroes[count]->getPos()) > dist)
						{
							dist = glm::distance(getPos(), heroes[count]->getPos());
							target = heroes[count];
						}
					}
					if (2 < dist && dist > 15)
					{
						state = STATE::MONSTER_MOVE;
					}
					else
						state = STATE::MONSTER_ATTACK;
	}
		break;
	default:
		break;
	}
}

void Character::Update()
{
	switch (role)
	{
	case ROLE::KNIGHT:
		switch (state)
		{
		case STATE::KNIGHT_MOVE:
			object->translation *= glm::translate(glm::normalize(target->getPos() - getPos()) * 0.3f);
			break;
		case STATE::KNIGHT_ATTACK:
			break;
		}
		break;
	case ROLE::ARCHER:
		switch (state)
		{
		case STATE::ARCHER_MOVE:
			object->translation *= glm::translate(glm::normalize(target->getPos() - getPos()) * 0.3f);
			break;
		case STATE::ARCHER_ATTACK:
			break;
		}
		break;
	case ROLE::HEALER:
		switch (state)
		{
		case STATE::HEALER_MOVE:
			object->translation *= glm::translate(glm::normalize(target->getPos() - getPos()) * 0.3f);
			break;
		case STATE::HEALER_HEAL:
			break;
		}
		break;
	case ROLE::MONSTER:
		switch (state)
		{
		case STATE::MONSTER_MOVE:
			object->translation *= glm::translate(glm::normalize(target->getPos() - getPos()));
			break;
		case STATE::MONSTER_ATTACK:
			break;
		}
	default:
		break;
	}
}