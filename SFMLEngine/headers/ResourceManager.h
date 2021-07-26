#pragma once
#include "ResourceLoader.h"


//You have to clean it yourself by calling CleanUp;
namespace SFENG {
	class ResourceManager {
	public:
		static ResourceManager& Get();
		sf::Texture& AddTexture(const std::string& filePath, const std::string& name);
		sf::Font& AddFont(const std::string& filePath, const std::string& name);
		sf::SoundBuffer& AddSoundBuffer(const std::string& filePath, const std::string& name);
		sf::Texture& GetTextrue(const std::string& name);
		sf::Font& GetFont(const std::string& name);
		sf::SoundBuffer& GetSoundBuffer(const std::string& name);
		void CleanUp();
	private:
		ResourceManager();
		static ResourceManager m_Instance;
		ResourceLoader<sf::Font>* m_FontLoader;
		ResourceLoader<sf::Texture>* m_TextureLoader;
		ResourceLoader<sf::SoundBuffer>* m_SoundBufferLoader;
	};
}