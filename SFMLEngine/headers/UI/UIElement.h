#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include "../Vec2.h"
#include "../Entity.h"


namespace SFENG {
	namespace UI {
		//enum class Type
		//{
		//	Button = 0,
		//	TextBox,
		//	SlideBar,
		//	Label,
		//	TypeCount
		//};
		class Canvas;
		class UIElement
		{
		public:
			UIElement(Canvas* parentCanvas, Entity* entity) 
				: m_Entity(entity), m_Canvas(parentCanvas)
			{}
			inline operator Entity*& () { return m_Entity; }
			~UIElement() = default;
		protected:
			virtual void Initialize() = 0;
			Entity* m_Entity;
			Canvas* m_Canvas;
		};
	}
}