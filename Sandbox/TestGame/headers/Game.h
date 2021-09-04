#pragma once
#include "PCH.h"

namespace en = SFENG;
class Game : public en::Engine {
public:
	Game();
	~Game();
	void HandleScenes() override;
private:

};