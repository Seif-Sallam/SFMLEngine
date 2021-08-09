#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <array>
#include <vector>
#include <bitset>
#include <map>
namespace SFENG 
{
	using ComponentTypeID = std::uint32_t;

	class Entity;
	class Component;
	static ComponentTypeID lastID = 0u;

	constexpr uint32_t MAX_ENTITIES = 5000u;
	constexpr uint32_t MAX_COMPONANTS = 32u;

	using ComponentBitset = std::bitset<MAX_COMPONANTS>;
	using ComponentArray = std::array<Component*, MAX_COMPONANTS>;
}