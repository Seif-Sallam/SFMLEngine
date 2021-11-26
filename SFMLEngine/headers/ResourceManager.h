#pragma once
#include "ResourceLoader.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

//You have to clean it yourself by calling CleanUp;
namespace SFENG {

	/// <summary>
	/// ResourceManager class a signelton used to Load and get textures, fonts, and sounds
	/// </summary>
	class ResourceManager {
	public:
		static sf::Texture& AddTexture(const std::string& filePath, const std::string& name);
		static sf::Font& AddFont(const std::string& filePath, const std::string& name);
		static sf::SoundBuffer& AddSoundBuffer(const std::string& filePath, const std::string& name);
		static sf::Texture& GetDefaultTexture();
		static sf::Texture& GetTextrue(const std::string& name);
		static sf::Font& GetFont(const std::string& name);
		static sf::Font& GetDefaultFont();
		static sf::SoundBuffer& GetSoundBuffer(const std::string& name);
		void CleanUp();
	private:
		static ResourceManager& Get();
		sf::Texture& AddTextureM(const std::string& filePath, const std::string& name);
		sf::Font& AddFontM(const std::string& filePath, const std::string& name);
		sf::SoundBuffer& AddSoundBufferM(const std::string& filePath, const std::string& name);
		sf::Texture& GetDefaultTextureM();
		sf::Texture& GetTextrueM(const std::string& name);
		sf::Font& GetFontM(const std::string& name);
		sf::Font& GetDefaultFontM();
		sf::SoundBuffer& GetSoundBufferM(const std::string& name);


		ResourceManager();
		static ResourceManager m_Instance;
		ResourceLoader<sf::Font>* m_FontLoader;
		ResourceLoader<sf::Texture>* m_TextureLoader;
		ResourceLoader<sf::SoundBuffer>* m_SoundBufferLoader;
	};
}