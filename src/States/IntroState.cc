#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Texture>("play", "resources/Buttons/button_play.png");
	engine.Load<ge::Resources::Texture>("settings", "resources/Buttons/button_settings.png");
	engine.Load<ge::Resources::Texture>("quit", "resources/Buttons/button_quit.png");

	ge::Vector2u size = engine.GetSize();
	world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5), "", "arial", START, "play");
	world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 2), "", "arial", SETTINGS, "settings");
	world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 3), "", "arial", QUIT, "quit");
	return true;
}

void IntroState::Clear() {
}

void IntroState::Pause() {
}

void IntroState::Resume() {
}

void IntroState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event)
{
		if (event.button == sf::Mouse::Button::Left)
		{
			for (auto const & it : world_.buttons)
			{
				if(&it->GetComponent<ge::Sprite>() != nullptr)
				{
					sf::Sprite t(engine.Texture(it->GetComponent<ge::Sprite>().textureName));
					t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
					if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y)))
					{
						switch (it->GetComponent<ge::Input>().id)
						{
							case START:
							engine.PushState("Login");
							break;
							case QUIT:
							engine.Quit();
							break;
							default:
							break;
						}
					}
				}
			}
		}
}

void IntroState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			HandleClick_(engine, event.mouseButton);
		default:
			break;
	}
}

void IntroState::Update(ge::GameEngine const & game)
{
}

void IntroState::Display(ge::GameEngine & engine, const float)
{
	for (auto const & it : world_.buttons)
	{
		sf::Text t(it->GetComponent<ge::Text>().text, engine.Font(it->GetComponent<ge::Text>().fontName));
		t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
		engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);

		if(&it->GetComponent<ge::Sprite>() != nullptr)
		{
			sf::Sprite s(engine.Texture(it->GetComponent<ge::Sprite>().textureName));
			s.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<ge::Sprite>().priority);
		}
	}
}
