#include "PlayWorld.h"
using ge::Velocity;
using ge::Position;
using ge::Sprite;
using ge::Collider;

void PlayWorld::CreatePlayer(ge::Vector2f const & t_position, ge::Vector2f const & t_velocity)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(t_position);
	g->AddComponent<ge::Velocity>(t_velocity);
	g->AddComponent<ge::Animator>();
	ge::Animation walk;
	walk.priority = 1;
	walk.speed = 50;
	for (uint32_t i = 1; i <= 10; ++i) {
		walk.sprites.push_back("resources/knight/Walk (" + std::to_string(i) + ").png");
	}
	ge::Animation attack;
	attack.priority = 1;
	attack.speed = 75;
	for (uint32_t i = 1; i <= 10; ++i) {
		attack.sprites.push_back("resources/knight/Attack (" + std::to_string(i) + ").png");
	}
	g->GetComponent<ge::Animator>()->AddAnimation("Walk", walk);
	g->GetComponent<ge::Animator>()->AddAnimation("Attack", attack);
	g->GetComponent<ge::Animator>()->SetAnimation("Walk");
	this->players.push_back(std::move(g));
}

void PlayWorld::CreatePlayer(Vector2f const & t_position, std::string const & t_textureName, Vector2f const & t_velocity)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Sprite>(t_textureName, 2);
	g->AddComponent<Collider>(t_position,Vector2f(60,60),"Player");
	this->players.push_back(std::move(g));
}

void PlayWorld::CreateShoot(Vector2f const & t_position, Vector2f const & t_velocity, std::string const & t_textureName)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Sprite>(t_textureName, 2);
	g->AddComponent<Collider>(t_position, Vector2f(30, 15), "Player Shoot");
	this->projectiles.push_back(std::move(g));
}
