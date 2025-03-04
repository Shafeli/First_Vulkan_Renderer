
#include <functional>

#include "TestingScene.h"
#include "../gap-311/VulkanShaderLibrary.hpp"
#include "../gap-311/VulkanWrapper.hpp"
#include "CoreSystems/CoreSystems.h"
#include "Renderer/VulkanRenderer.h"
#include "SceneManager/SceneManager.h"
#include "WindowHandle/WindowHandle.h"


int main(int argc, char* argv[])
{

	const char* appName = argv[0];

	Brokkr::CoreSystems CoreSystemsManager;

	CoreSystemsManager.Init("VulkanFPSCame", 1280, 720);

    const auto pWindow = CoreSystemsManager.GetCoreSystem<Brokkr::WindowHandle>();
	pWindow->InitWindow("VulkanFPSCame", 1280, 720);

    const auto pVulkanRenderer = CoreSystemsManager.AddCoreSystem<Brokkr::VulkanRenderer>();
	pVulkanRenderer->Init(std::filesystem::path(argv[0]).parent_path().string(), pWindow);

	const auto pSceneManager = CoreSystemsManager.GetCoreSystem<Brokkr::SceneManager>();

	pSceneManager->AddState("Testing", std::make_unique<TestingScene>(&CoreSystemsManager));
	pSceneManager->SetActiveState("Testing");

	CoreSystemsManager.Run();
	CoreSystemsManager.Destroy();
	return 0;
}
