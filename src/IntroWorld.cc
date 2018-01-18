#include "IntroWorld.h"

void IntroWorld::CreateButton(ge::Vector2f const & pos, std::string const & text, std::string const & font, int input)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(pos);
	g->AddComponent<ge::Text>(text, font);
	g->AddComponent<ge::Input>(input);

	this->buttons.push_back(std::move(g));
}