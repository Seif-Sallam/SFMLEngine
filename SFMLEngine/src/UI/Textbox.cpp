#include "UI/Textbox.h"
#include "UI/Canvas.h"
#include "UI/UIElement.h"

#include "Entity.h"
#include "ResourceManager.h"


SFENG::UI::Textbox::Textbox(SFENG::Entity *entity, Canvas *parentCanvas)
	: UIElement(parentCanvas, entity), m_Active(false)
{
	Initialize();
}

void SFENG::UI::Textbox::Initialize()
{
	Transform &boxTrans = entity->GetComponent<Transform>();
	SFENG::Entity *&canvasEntity = m_Canvas->entity;
	Transform &canvasTrans = canvasEntity->GetComponent<Transform>();
	boxTrans.position = canvasTrans.position;
	boxTrans.size = {50.0f, 25.0f};
	m_TextEnterHandler = &entity->AddComponent<TextEnterHandler>();
	m_TextEnterHandler->SetFont("Default");
	Highlightable &hightlightable = this->entity->AddComponent<Highlightable>();
	hightlightable.ListenToKeys(true);
	Selected *sel = &entity->AddComponent<Selected>();
	entity->AddComponent<TextBoxSelection>();
}

bool SFENG::UI::Textbox::TextBoxSelection::Init()
{
	m_SelectedComp = &entity->GetComponent<Selected>();
	m_TxtEnterHandler = &entity->GetComponent<TextEnterHandler>();
	return Component::Init();
}

void SFENG::UI::Textbox::TextBoxSelection::HandleEvents(sf::Event &event)
{
	if (m_SelectedComp->IsPressed())
		m_TxtEnterHandler->Activate();
	else
		m_TxtEnterHandler->Deactivate();
}