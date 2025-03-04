#pragma once

#include <glm/fwd.hpp>

#include "../CoreSystems/CoreSystems.h"
#include "../../gap-311/VulkanWrapper.hpp"
#include "../../gap-311/VulkanShaderLibrary.hpp"

//TODO: Finish later
namespace Brokkr
{
    class WindowHandle;

    class VulkanRenderer : public Brokkr::CoreSubsystem
    {
        GAP311::VulkanWrapper vulkan;
        GAP311::VulkanShaderLibrary shaderLib;

        std::shared_ptr<GAP311::VulkanWrapper::GraphicsPipeline> gridPipeline;
        std::shared_ptr<GAP311::VulkanWrapper::GraphicsPipeline> meshPipeline;

        vk::Buffer cubeIndexBuffer;
        vk::Buffer cubeVertexBuffer;
        uint32_t cubeIndexCount = 0;

        std::vector<glm::mat4> cubeTransforms;

        vk::Buffer pyramidIndexBuffer;
        vk::Buffer pyramidVertexBuffer;
        uint32_t pyramidIndexCount = 0;

        std::vector<glm::mat4> pyramidTransforms;

        GAP311::VulkanWrapper::ShaderUniform cameraUniform;

        GAP311::VulkanWrapper m_VulkanContext;                                       // Vulkan instance
        GAP311::VulkanShaderLibrary m_ShaderLibrary;                                 // Shader Manager
        std::shared_ptr<GAP311::VulkanWrapper::GraphicsPipeline> m_GraphicsPipeline; // Main Graphics Pipeline
        Brokkr::WindowHandle* m_pWindow = nullptr;
        VkSurfaceKHR m_surface;

    public:
        explicit VulkanRenderer(CoreSystems* pCoreManager);

        void Init(const std::string& argv, Brokkr::WindowHandle* pWindowHandle);    // Initialize Vulkan

        void CreatePipeline();

        VkDevice_T* GetDevice()
        {
            return m_VulkanContext.GetDevice();
        }


        virtual void Destroy() override;
    };
}