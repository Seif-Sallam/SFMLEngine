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
		enum class UIElementType {
			Button = 0,
			TextBox,
			SlideBar,
			Label,
			Image,
			TypeCount
		};
		class Canvas 
		{
		public:
			Canvas(const std::string& name, LifeCycleManager& LCM);
			std::string AddElement(const std::string& name, UIElementType type);
			UIElement* GetElement(const std::string& name);
			~Canvas();
			Entity* entity;
		private:
			void AddElementPriv(const std::string& name, UIElement*& element);
			std::string GetNewName(const std::string& name);
			LifeCycleManager& m_LCM;
			std::map<std::string, UIElement*> m_Elements;
			std::map<std::string, int32_t> m_ElementsNums;
		};
	}
}