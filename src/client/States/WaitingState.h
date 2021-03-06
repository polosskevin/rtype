#ifndef WaitingState_H_
#define WaitingState_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuValue.h"
#include "MenuState.h"

class WaitingState : public MenuState {
public:
	WaitingState() = default;
	WaitingState(WaitingState const & other) = delete;
	WaitingState(WaitingState && other) = delete;
	~WaitingState() override = default;

	WaitingState & operator=(WaitingState const & other) = delete;
	WaitingState & operator=(WaitingState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
	void UpdateList(ge::Vector2u const & size);
};

#endif /*WaitingState_H_*/
