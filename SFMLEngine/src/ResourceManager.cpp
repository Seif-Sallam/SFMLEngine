#include "ResourceManager.h"
SFENG::ResourceManager SFENG::ResourceManager::m_Instance;

SFENG::ResourceManager& SFENG::ResourceManager::Get()
{
	return m_Instance;
}

sf::Texture& SFENG::ResourceManager::AddTexture(const std::string& filePath, const std::string& name)
{
	// TODO: insert return statement here
	return m_Instance.AddTextureM(filePath, name);
}

sf::Texture& SFENG::ResourceManager::AddTextureM(const std::string& filePath, const std::string& name)
{
	return m_TextureLoader->Add(filePath, name);
}

sf::Font& SFENG::ResourceManager::AddFontM(const std::string& filePath, const std::string& name)
{
	return m_FontLoader->Add(filePath, name);
}

sf::SoundBuffer& SFENG::ResourceManager::AddSoundBufferM(const std::string& filePath, const std::string& name)
{
	return m_SoundBufferLoader->Add(filePath, name);
}

sf::Texture& SFENG::ResourceManager::GetDefaultTextureM()
{
	return m_TextureLoader->Get("Default");
}

sf::Texture& SFENG::ResourceManager::GetTextrueM(const std::string& name)
{
	return m_TextureLoader->Get(name);
}

sf::Font& SFENG::ResourceManager::GetFontM(const std::string& name)
{
	return m_FontLoader->Get(name);
}

sf::Font& SFENG::ResourceManager::GetDefaultFontM()
{
	return m_FontLoader->Get("Default");
}

sf::SoundBuffer& SFENG::ResourceManager::GetSoundBufferM(const std::string& name)
{
	return m_SoundBufferLoader->Get(name);
}

sf::Font& SFENG::ResourceManager::AddFont(const std::string& filePath, const std::string& name)
{
	// TODO: insert return statement here
	return m_Instance.AddFontM(filePath, name);
}

sf::SoundBuffer& SFENG::ResourceManager::AddSoundBuffer(const std::string& filePath, const std::string& name)
{
	// TODO: insert return statement here
	return m_Instance.AddSoundBufferM(filePath, name);
}

sf::Texture& SFENG::ResourceManager::GetDefaultTexture()
{
	return m_Instance.GetDefaultTextureM();
}

sf::Texture& SFENG::ResourceManager::GetTextrue(const std::string& name)
{
	return m_Instance.GetTextrueM(name);
}

sf::Font& SFENG::ResourceManager::GetFont(const std::string& name)
{
	// TODO: insert return statement here
	return m_Instance.GetFontM(name);
}

sf::Font& SFENG::ResourceManager::GetDefaultFont()
{
	// TODO: insert return statement here
	return m_Instance.GetDefaultFontM();
}

sf::SoundBuffer& SFENG::ResourceManager::GetSoundBuffer(const std::string& name)
{
	// TODO: insert return statement here
	return m_Instance.GetSoundBufferM(name);
}

void SFENG::ResourceManager::CleanUp()
{
	delete m_FontLoader;
	delete m_TextureLoader;
	delete m_SoundBufferLoader;
}

SFENG::ResourceManager::ResourceManager()
{
	m_FontLoader = new ResourceLoader<sf::Font>("../SFMLEngine/rsc/failed/arial.ttf");
	m_TextureLoader = new ResourceLoader<sf::Texture>("../SFMLEngine/rsc/failed/failed.png");
	m_SoundBufferLoader = new ResourceLoader<sf::SoundBuffer>("../SFMLEngine/rsc/failed/Silent.wav");
}