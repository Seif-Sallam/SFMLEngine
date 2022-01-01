#pragma once
#include "PCH.h"

class MazeGenerator;
class MazeController : public SFENG::Component
{
public:
    MazeController();
    bool Init() override;
    void ImGuiLayer() override;
    void SetMazeGenerator(MazeGenerator *gen);

private:
    MazeGenerator *m_MazeGen;
    int m_Count = 0;
};