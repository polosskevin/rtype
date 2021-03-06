#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "AGameState.h"
#include "PlayWorld.h"
#include "UDPNonBlockingCommunication.h"
#include "Events.h"
#include "IArtificialIntelligence.hpp"


class PlayState : public ge::AGameState {
public:
	PlayState(std::shared_ptr<ge::network::UDPNonBlockingCommuncation> & t_udp);
	PlayState(PlayState const & other) = delete;
	PlayState(PlayState && other) = delete;
	~PlayState() override = default;

	PlayState & operator=(PlayState const & other) = delete;
	PlayState & operator=(PlayState && other) = delete;

	bool Init(ge::GameEngine & engine) override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent(ge::GameEngine & engine, sf::Event const & event) override;
	void Update(ge::GameEngine & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

private:
	void HandlePlayerMovement_(ge::GameEngine const & engine, sf::Keyboard::Key const & key);
	void HandlePlayerAnimation_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event);
	void HandleQuit_(ge::GameEngine & engine, sf::Event::KeyEvent const & event);
	void HandleUdp_(void *data, std::size_t nbyte);


	bool 			endGame_;
	PlayWorld world_;
	std::shared_ptr<ge::network::UDPNonBlockingCommuncation> udp_;
	std::chrono::time_point<std::chrono::high_resolution_clock> time_;
	std::vector<std::string> playersSprites_;
	std::vector<rtype::protocol_udp::Event> events_;
	std::vector<Vector2f> starpos_;
};

#endif /*PLAYSTATE_H_*/
