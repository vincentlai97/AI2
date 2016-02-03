#include "MyModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

#include "Character.h"

MyModel::MyModel() : Model_3D()
{
	for (auto iter : all_weapon_commands)
		weapon_commands[iter] = false;
}

MyModel::~MyModel()
{
}



enum STATS
{
	STR,
	DEX,
	INT
};


void RandomiseStats(Character *character);
void UpdateRoles();

static Mesh *mesh;
static Object *object;
static SceneNode *node;

std::array<Character *, 3> heroes;
Mesh *knightMesh;
Mesh *archerMesh;
Mesh *healerMesh;
Character *monster;
static std::vector<Character *> monsters;
Mesh *monsterMesh;

void MyModel::Init()
{
	srand(time(NULL));

	camera.Init(Vector3(0, 0, 5), Vector3(), Vector3(0, 1, 0));

	knightMesh = MeshBuilder::GenerateSphere("", Color(1, 0, 0), 4, 32, 1);
	archerMesh = MeshBuilder::GenerateSphere("", Color(0, 1, 0), 4, 32, 1);
	healerMesh = MeshBuilder::GenerateSphere("", Color(0, 0, 1), 4, 32, 1);
	monsterMesh = MeshBuilder::GenerateSphere("", Color(0.5, 0.5, 0), 4, 16, 1);

	for (int count = 0; count < 3; ++count)
		heroes[count] = new Character();

	object = new Object();
	object->translation = glm::translate(-30, 10, 0);
	m_objectList.push_back(object);
	heroes[0]->object = object;

	object = new Object();
	object->translation = glm::translate(-30, 0, 0);
	m_objectList.push_back(object);
	heroes[1]->object = object;

	object = new Object();
	object->translation = glm::translate(-30, -10, 0);
	m_objectList.push_back(object);
	heroes[2]->object = object;

	object = new Object(monsterMesh);
	m_objectList.push_back(object);
	monster = new Character();
	monster->object = object;
	monster->role = ROLE::MONSTER;
	monsters.push_back(monster);
	

	for (int count = 0; count < 3; ++count)
		RandomiseStats(heroes[count]);
	UpdateRoles();
}

void MyModel::Update(double dt)
{
	Model_3D::Update(dt);

	system("cls");
	for (int count = 0; count < 3; ++count)
	{
		std::cout << "Hero " << (char)('0' + count) << ": ";
		switch (heroes[count]->role)
		{
		case ROLE::KNIGHT:
			std::cout << "Knight";
			break;
		case ROLE::ARCHER:
			std::cout << "Archer";
			break;
		case ROLE::HEALER:
			std::cout << "Healer";
			break;
		}
		std::cout << std::endl;
	}

	for (int count = 0; count < 3; ++count)
	{
		heroes[count]->UpdateState(heroes, monsters);
	}
	monster->UpdateState(heroes, monsters);
	for (int count = 0; count < 3; ++count)
	{
		heroes[count]->Update();
	}
	monster->Update();
}

void RandomiseStats(Character *character)
{
	character->stats[STR] = rand() % 100;
	character->stats[DEX] = rand() % 100;
	character->stats[INT] = rand() % 100;
	character->hp = character->stats[STR];
}

//#define stats(x, y) heroes[x].stats[y]
#define cmp_stats(x, y, z) heroes[x]->stats[z] < heroes[y]->stats[z]
#define add_weights(x, y, z, w) weights[0][w] = x; weights[1][w] = y; weights[2][w] = z

void UpdateRoles()
{
	std::array<std::array<float, 3>, 3> weights;

	for (int count = 0; count < 3; ++count)
	{
		if (cmp_stats(0, 1, count)) // 0 < 1
		{
			if (cmp_stats(0, 2, count)) // 0 < 2
			{
				if (cmp_stats(1, 2, count)) // 0 < 1 < 2
				{
					add_weights(0.8, 1, 1.2, count);
				}
				else if (cmp_stats(2, 1, count)) // 0 < 2 < 1
				{
					add_weights(0.8, 1.2, 1, count);
				}
				else // 0 < 1 = 2
				{
					add_weights(0.8, 1.2, 1.2, count);
				}
			}
			else if (cmp_stats(2, 0, count)) // 2 < 0 < 1
			{
				add_weights(1, 1.2, 0.8, count);
			}
			else // 0 = 2 < 1
			{
				add_weights(0.8, 1.2, 0.8, count);
			}
		}
		else if (cmp_stats(1, 0, count)) // 1 < 0
		{
			if (cmp_stats(0, 2, count)) // 1 < 0 < 2
			{
				add_weights(1, 0.8, 1.2, count);
			}
			else if (cmp_stats(2, 0, count)) // 2 < 0
			{
				if (cmp_stats(1, 2, count)) // 1 < 2 < 0
				{
					add_weights(1.2, 0.8, 1, count);
				}
				else if (cmp_stats(2, 1, count)) // 2 < 1 < 0
				{
					add_weights(1.2, 1, 0.8, count);
				}
				else // 1 = 2 < 0
				{
					add_weights(1.2, 0.8, 0.8, count);
				}
			}
			else // 1 < 0 = 2
			{
				add_weights(1.2, 0.8, 1.2, count);
			}
		}
		else // 0 = 1
		{
			if (cmp_stats(0, 2, count)) // 0 = 1 < 2
			{
				add_weights(0.8, 0.8, 1.2, count);
			}
			else if (cmp_stats(2, 0, count)) // 2 < 0 = 1
			{
				add_weights(1.2, 1.2, 0.8, count);
			}
			else // 0 = 1 = 2
			{
				add_weights(1.2, 1.2, 1.2, count);
			}
		}
	}

	for (int count = 0; count < 3; ++count)
	for (int _count = 0; _count < 3; ++_count)
	{
		weights[count][_count] *= heroes[count]->stats[_count];
	}

	float highest = 0;
	int hHero, hStat;
	for (int count = 0; count < 3; ++count)
	for (int _count = 0; _count < 3; ++_count)
	{
		if (weights[count][_count] > highest)
		{
			highest = weights[count][_count];
			hHero = count;
			hStat = _count;
		}
	}
	heroes[hHero]->role = (ROLE)hStat;
	highest = 0;
	int _hHero, _hStat;
	for (int count = 0; count < 3; ++count)
	for (int _count = 0; _count < 3; ++_count)
	{
		if (count != hHero && _count != hStat)
		if (weights[count][_count] > highest)
		{
			highest = weights[count][_count];
			_hHero = count;
			_hStat = _count;
		}
	}
	heroes[_hHero]->role = (ROLE)_hStat;
	for (int count = 0; count < 3; ++count)
	for (int _count = 0; _count < 3; ++_count)
	{
		if (count != hHero && _count != hStat)
		if (count != _hHero && _count != _hStat)
			heroes[count]->role = (ROLE)_count;
	}

	for (int count = 0; count < 3; ++count)
	{
		switch (heroes[count]->role)
		{
		case ROLE::KNIGHT:
			heroes[count]->object->mesh = knightMesh;
			break;
		case ROLE::ARCHER:
			heroes[count]->object->mesh = archerMesh;
			break;
		case ROLE::HEALER:
			heroes[count]->object->mesh = healerMesh;
			break;
		default:
			break;
		}
	}
}

//#undef stats(x, y)
#undef cmp_stats(x, y, z)
#undef add_weights(x, y, z, w)