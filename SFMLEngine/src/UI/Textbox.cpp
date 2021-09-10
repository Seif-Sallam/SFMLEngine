#include "../../headers/UI/Textbox.h"
#include "../../headers/UI/Canvas.h"
#include "../../headers/Entity.h"
#include "../../headers/ResourceManager.h"

SFENG::UI::Textbox::Textbox(Entity* entity, Canvas* parentCanvas)
	: UIElement(parentCanvas, entity)
{
	Initialize();
}

void SFENG::UI::Textbox::Initialize()
{
	Transform& boxTrans = entity->GetCopmonent<Transform>();
	Entity*& canvasEntity = m_Canvas->entity;
	Transform& canvasTrans = canvasEntity->GetCopmonent<Transform>();
	boxTrans.position = canvasTrans.position;
	boxTrans.size = { 50.0f, 25.0f };
	m_TextEnterHandler = &entity->AddComponent<TextEnterHandler>();
	m_TextEnterHandler->SetFont("Default");
}
