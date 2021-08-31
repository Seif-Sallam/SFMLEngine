#include "../../headers/Components/SpriteRenderer.h"
#include "../../headers/Entity.h"
#include "../../headers/ResourceManager.h"

SFENG::SpriteRenderer::SpriteRenderer()
	: Component(), m_Texture(nullptr), m_TextureName("UN_SET"), m_Transform(nullptr)
{
}

bool SFENG::SpriteRenderer::Init()
{
	m_Transform = &this->entity->GetCopmonent<Transform>();
	return Component::Init();
}

void SFENG::SpriteRenderer::AttachTexture(const std::string& textureName)
{
	m_TextureName = textureName;
	m_Texture = &SFENG::ResourceManager::Get().GetTextrue(textureName);
	m_Sprite.setTexture(*m_Texture);
	Vec2f size = { m_Sprite.getLocalBounds().width,	m_Sprite.getLocalBounds().height };
	m_Transform->size = size;
	m_Sprite.setOrigin(size / 2.f);
	m_Sprite.setPosition(m_Transform->position);
}

void SFENG::SpriteRenderer::SetRect(const sf::IntRect& rect)
{
	m_Sprite.setTextureRect(rect);
	if ((int)m_Transform->size.w != rect.width || (int)m_Transform->size.h != rect.height) {
		Vec2f size = { (float)rect.width, (float)rect.height };
		m_Transform->size = size;
		m_Sprite.setOrigin(size / 2.f);
		m_Sprite.setPosition(m_Transform->position);
	}
}

void SFENG::SpriteRenderer::Draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
	return Component::Draw(window);
}

void SFENG::SpriteRenderer::Update(const sf::Time& elapsedTime)
{
	m_Sprite.setPosition(m_Transform->position);
	m_Sprite.setRotation(m_Transform->angle);
	return Component::Update(elapsedTime);
}

void SFENG::SpriteRenderer::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::SpriteRenderer::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

void SFENG::SpriteRenderer::Print()
{
	std::cout << "Sprite Renderer\n";
	std::cout << "TextureName: " << m_TextureName;
}