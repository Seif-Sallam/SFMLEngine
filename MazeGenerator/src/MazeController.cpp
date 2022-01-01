#include "../headers/MazeController.h"
#include "../headers/MazeGenerator.h"

MazeController::MazeController()
{
}

bool MazeController::Init()
{
    if (this->entity->HasComponent<MazeGenerator>())
        m_MazeGen = &this->entity->GetComponent<MazeGenerator>();
    else
        m_MazeGen = nullptr;

    return Component::Init();
}

void MazeController::ImGuiLayer()
{
    ImGui::Begin("Maze controller");
    {
        if (m_MazeGen)
        {
            static int width = m_MazeGen->GetWidth();
            static int height = m_MazeGen->GetHeight();

            ImGui::TextUnformatted("Width:");
            ImGui::SameLine();
            ImGui::InputInt("###4", &width, 0);
            ImGui::TextUnformatted("Height:");
            ImGui::SameLine();
            ImGui::InputInt("###3", &height, 0);

            if (ImGui::Button("Set Width and Height"))
            {
                m_MazeGen->SetWidthAndHeight(width, height);
            }

            static int startX2 = m_MazeGen->startX;
            static int startY2 = m_MazeGen->startY;
            ImGui::TextUnformatted("Start X position:");
            ImGui::SameLine();
            ImGui::SliderInt("###2", &startX2, 0, m_MazeGen->GetWidth());
            ImGui::TextUnformatted("Start Y position:");
            ImGui::SameLine();
            ImGui::SliderInt("###5", &startY2, 0, m_MazeGen->GetHeight());

            if (ImGui::Button("Set start X and start Y"))
            {
                m_MazeGen->startX = startX2;
                m_MazeGen->startY = startY2;
                m_MazeGen->Reset();
            }

            ImGui::Separator();
            if (ImGui::Button("Take Step"))
            {
                if (!m_MazeGen->IsRunning())
                    m_MazeGen->Run(true);
                m_MazeGen->TakeStep();
            }

            if (ImGui::Button("Reset"))
            {
                m_MazeGen->Reset();
            }
            ImGui::Separator();
            ImGui::Text("Current cell: x: %d, y: %d", m_MazeGen->GetCurrentCell()->GetX(), m_MazeGen->GetCurrentCell()->GetX());
        }
        else
        {
            ImGui::TextUnformatted("Maze Generator is nullptr");
        }
    }
    ImGui::End();
    ImGui::Begin("Alive entities count");
    ImGui::Text("Alive entities: %d", SFENG::LCM::GetAliveEntites());
    ImGui::Text("Drawn entities: %d", SFENG::LCM::s_OnGoingLCM->GetNumberOfDrawnEntities());
    ImGui::End();
}

void MazeController::SetMazeGenerator(MazeGenerator *gen)
{
    m_MazeGen = gen;
}
