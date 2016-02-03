#include "Character.h"

#include "gtx\transform.hpp"

void Character::UpdateState(std::array<Character *, 3> heroes, std::vector<Character *> monsters, double dt)
{
	float monsterDist = 100;
	Character *monster;
	for (Character *iter : monsters)
	{
		if (glm::distance(iter->getPos(), getPos()) < monsterDist)
		{
			monsterDist = glm::distance(iter->getPos(), getPos());
			monster = iter;
		}
	}
	switch (role)
	{
	case ROLE::KNIGHT:
		if (monsterDist < 2)
		{
			state = STATE::KNIGHT_ATTACK;
		}
		else if (monsterDist < 15)
		{
			state = STATE::KNIGHT_MOVE;
			target = monster;
		}
		else
			state = STATE::KNIGHT_IDLE;
		break;
	case ROLE::ARCHER:
		if (attacked)
		{
			if (glm::distance(getPos(), attacker->getPos()) > 5) attacked = false;
			else state = STATE::ARCHER_RETREAT;
		}
		if (!attacked)
		{
			if (monsterDist < 10)
			{
				state = STATE::ARCHER_ATTACK;
			}
			else if (monsterDist < 20)
			{
				state = STATE::ARCHER_MOVE;
				target = monster;
			}
			else
				state = STATE::ARCHER_IDLE;
		}
		break;
	case ROLE::HEALER:
		if (attacked)
		{
			if (glm::distance(getPos(), attacker->getPos()) > 5) attacked = false;
			else state = STATE::ARCHER_RETREAT;
		}
		if (!attacked)
		{
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
		}
		break;
	case ROLE::MONSTER:
	{
						  Character closestHero;
						  float dist = 15;
						  for (int count = 0; count < 3; ++count)
						  {
							  if (glm::distance(getPos(), heroes[count]->getPos()) < dist)
							  {
								  dist = glm::distance(getPos(), heroes[count]->getPos());
								  target = heroes[count];
								  targetReached = true;
							  }
						  }
						  if (dist < 2)
							  state = STATE::MONSTER_ATTACK;
						  else if (dist < 15)
							  state = STATE::MONSTER_MOVE;
						  else
						  {
							  if (!targetReached)
							  {
								  if (glm::distance(getPos(), target->getPos()) < 2)
								  {
									  delete target;
									  targetReached = true;
								  }
							  }
							  if (targetReached)
							  {
								  target = new Character();
								  target->object = new Object();
								  target->object->translation = glm::translate(glm::vec3(rand() % 100 - 50, rand() % 80 - 40, 0));
								  state = STATE::MONSTER_PATROL;
								  targetReached = false;
							  }
						  }
	}
		break;
	default:
		break;
	}
}

void Character::Update(double dt)
{
	attackBuffer -= dt;

	switch (role)
	{
	case ROLE::KNIGHT:
		switch (state)
		{
		case STATE::KNIGHT_IDLE:
			break;
		case STATE::KNIGHT_MOVE:
			Move(target->getPos() - getPos(), dt);
			break;
		case STATE::KNIGHT_ATTACK:
			if (attackBuffer < 0)
			{
				if (target != NULL)
					target->hp -= 10;
				attackBuffer = 0.5f;
			}
			break;
		}
		break;
	case ROLE::ARCHER:
		switch (state)
		{
		case STATE::ARCHER_IDLE:
			break;
		case STATE::ARCHER_MOVE:
			Move(target->getPos() - getPos(), dt);
			break;
		case STATE::ARCHER_ATTACK:
			if (attackBuffer < 0)
			{
				if (target != NULL)
					target->hp -= 10;
				attackBuffer = 0.5f;
			}
			break;
		case STATE::ARCHER_RETREAT:
			Move(getPos() - attacker->getPos(), dt);
			break;
		}
		break;
	case ROLE::HEALER:
		switch (state)
		{
		case STATE::HEALER_MOVE:
			Move(target->getPos() - getPos(), dt);
			break;
		case STATE::HEALER_HEAL:
			if (target != NULL)
			if (attackBuffer < 0 && target->hp < target->getMaxHP())
			{
				target->hp += 10;
				attackBuffer = 2.f;
			}
			break;
		case STATE::HEALER_RETREAT:
			Move(getPos() - attacker->getPos(), dt);
			break;
		}
		break;
	case ROLE::MONSTER:
		switch (state)
		{
		case STATE::MONSTER_PATROL:
		case STATE::MONSTER_MOVE:
			Move(target->getPos() - getPos(), dt);
			break;
		case STATE::MONSTER_ATTACK:
			if (attackBuffer < 0)
			{
				if (target != NULL)
					target->hp -= 10;
				attackBuffer = 0.5f;
			}
			target->attacked = true;
			target->attacker = this;
			break;
		}
	default:
		break;
	}
}

void Character::Move(glm::vec3 direction, double dt)
{
	if (direction.x < 0 && getPos().x < -50) direction.x = 0;
	else if (direction.x > 0 && getPos().x > 50) direction.x = 0;
	if (direction.y < 0 && getPos().y < -40) direction.y = 0;
	else if (direction.y > 0 && getPos().y > 40) direction.y = 0;
	if (direction.length() != 0)
		object->translation *= glm::translate(glm::normalize(direction) * (float)dt * (8.f + stats[1] / 25.f));
}