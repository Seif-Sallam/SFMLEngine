#include "../headers/ResourceManager.h"
SFENG::ResourceManager SFENG::ResourceManager::m_Instance;

SFENG::ResourceManager& SFENG::ResourceManager::Get()
{
	return m_Instance;
}

sf::Texture& SFENG::ResourceManager::AddTexture(const std::string& filePath, const std::string& name)
{
	return m_TextureLoader->Add(filePath, name);
}

sf::Font& SFENG::ResourceManager::AddFont(const std::string& filePath, const std::string& name)
{
	return m_FontLoader->Add(filePath, name);
}

sf::SoundBuffer& SFENG::ResourceManager::AddSoundBuffer(const std::string& filePath, const std::string& name)
{
	return m_SoundBufferLoader->Add(filePath, name);
}

sf::Texture& SFENG::ResourceManager::GetDefaultTexture()
{
	return m_TextureLoader->Get("Default");
}

sf::Texture& SFENG::ResourceManager::GetTextrue(const std::string& name)
{
	return m_TextureLoader->Get(name);
}

sf::Font& SFENG::ResourceManager::GetFont(const std::string& name)
{
	return m_FontLoader->Get(name);
}

sf::Font& SFENG::ResourceManager::GetDefaultFont()
{
	return m_FontLoader->Get("Default");
}

sf::SoundBuffer& SFENG::ResourceManager::GetSoundBuffer(const std::string& name)
{
	return m_SoundBufferLoader->Get(name);
}

void SFENG::ResourceManager::CleanUp()
{
	delete m_FontLoader;
	delete m_TextureLoader;
	delete m_SoundBufferLoader;
}

SFENG::ResourceManager::ResourceManager()
	: m_FontLoader(new ResourceLoader<sf::Font>("rsc/failed/arial.ttf")),
	m_TextureLoader(new ResourceLoader<sf::Texture>("rsc/failed/failed.png")),
	m_SoundBufferLoader(new ResourceLoader<sf::SoundBuffer>("rsc/failed/Silent.wav"))
{
}