#pragma once
#include "imgui.h"

namespace SFENG {
	namespace UI
	{
		enum class GUIElement {
			Button,
			Text,
			SlideBar,
			ColorPick
		};


		class Element {
		public:
			Element(GUIElement type) {}

		private:
			GUIElement m_Type;

		};
	}
}