#pragma once
#include "Component.h"
#include "../Mouse.h"

namespace SFENG {
	class Transform;
	class Highlightable : public Component {
	public:
		Highlightable();
		bool Init() override;
		bool IsHighlighted();
		void ListenToKeys(bool value);
		sf::Mouse::Button KeyPressed();
	private:
		bool m_ListenToKeys;
		Transform* m_Trans;
	};
}