#pragma once
#include "PCH.h"

namespace en = SFENG;
class MainMenu : public en::Scene 
{
public:
	MainMenu(en::Engine& engine, b2World& phys);
	~MainMenu();
protected:
	void Main() override final;

private:
	std::map<std::string, en::Entity*> m_Entities;
};