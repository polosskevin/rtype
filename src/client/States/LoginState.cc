#include "LoginState.h"
bool LoginState::Init(ge::GameEngine & engine) {
	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), "Login: " + login, "retro");
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 2), "Create",  "retro", CREATE);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 3), "Join", "retro", JOIN);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 4), "Cancel", "retro", CANCEL);
	world_.CreateBackground();
	return true;
}


void LoginState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event)
{
	for (auto const & it : world_.texts)
	{
		if (it->GetComponent<ge::Text>()->text == ("Login: " + login))
		{
			login += static_cast<char>(event.unicode);
			it->GetComponent<ge::Text>()->text += event.unicode;
		}
	}
}

void LoginState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.texts) {
		if(it->GetComponent<ge::Text>())
		{
			sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
			t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
				if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
					switch (it->GetComponent<ge::Input>()->id) {
						case CREATE:
							engine.PushState("Create");
							break;
						case JOIN:
							engine.PushState("Join");
							break;
						case CANCEL:
							engine.PopState();
							break;
						default:
							break;
					}
				}
			}
		}
	}
}
