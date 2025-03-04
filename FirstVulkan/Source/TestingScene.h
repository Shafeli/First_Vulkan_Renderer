#pragma once

#include "SceneManager/Scene.h"

class TestingScene : public Brokkr::Scene
{

public:
    explicit TestingScene(Brokkr::CoreSystems* pCoreManager);

    void Init() override;
    void Update() override;
    void Exit() override;
    void Enter() override;
    void Destroy() override;

};
