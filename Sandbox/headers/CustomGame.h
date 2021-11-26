#pragma once
#include "PCH.h"
#include "CustomScene.h"

class CustomGame : public SFENG::Engine {
public:
	CustomGame();
	~CustomGame();
	void HandleScenes() override;
private:
};
