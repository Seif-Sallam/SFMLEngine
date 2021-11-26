#pragma once

#include "PCH.h"


class Game : public SFENG::Engine {
public:
	Game();
	~Game();
	void HandleScenes() override;

private:
};