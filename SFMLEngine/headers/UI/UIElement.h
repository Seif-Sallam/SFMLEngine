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
		class Canvas;
		class UIElement
		{
		public:
			UIElement(Canvas* parentCanvas, Entity* entity) 
				: entity(entity), m_Canvas(parentCanvas)
			{}
			~UIElement() = default;
			Entity* entity;
		protected:
			virtual void Initialize() = 0;
			Canvas* m_Canvas;
		};
	}
}