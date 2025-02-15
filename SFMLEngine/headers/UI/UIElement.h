#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include "Vec2.h"


namespace SFENG {
	class Entity;

	namespace UI {
		class Canvas;
		class UIElement
		{
		public:
			UIElement(Canvas* parentCanvas, Entity* entity)
				: entity(entity), m_Canvas(parentCanvas)
			{}
			virtual ~UIElement() = default;

			Entity* entity;
		protected:
			virtual void Initialize() = 0;

			Canvas* m_Canvas;
		};
	}
}