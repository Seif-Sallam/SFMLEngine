#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "../Vec2.h"
#include "UIElement.h"
#include "../Entity.h"
#include "../Components/Component.h"

namespace SFENG {
	class LifeCycleManager;
	namespace UI {
		class Canvas 
		{
		public:
			Canvas(LifeCycleManager& LCM);
			std::string AddElement(const std::string& name, UIElement* elemnt);
			UIElement* GetElement(const std::string& name);
			~Canvas();
			inline operator Entity*&() { return m_Entity; }
		private:
			LifeCycleManager& m_LCM;
			Entity* m_Entity;
			std::map<std::string, UIElement*> m_Elements;
			std::map<std::string, int32_t> m_ElementsNums;
		};
	}
}