/*
		UNDER_CONSTRUCTION :D
*/
//#pragma once
//#include <string>
//#include <vector>
//#include <map>
//#include "Component.h"
//#include "../Keyboard.h"
//
//typedef void(*FunctionPtr)();
//
//namespace SFENG {
//	class Controller : public Component
//	{
//	public:
//		Controller();
//		~Controller();
//
//		void AddEvent(const std::string&, FunctionPtr function);
//		inline bool Init() override;
//		inline void Draw(sf::RenderWindow& window) override;
//		inline void Update(const sf::Time& elapsedTime) override;
//		inline void FixedUpdate(const sf::Time& elapsedTime) override;
//		inline void HandleEvents(sf::Event& event) override;
//		inline void Print() override;
//	
//	private:
//		std::map<std::string,FunctionPtr> m_Functions;
//		
//	};
//
//}