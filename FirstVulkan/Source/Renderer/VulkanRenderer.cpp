#include "VulkanRenderer.h"

#include <glm/ext/matrix_transform.hpp>
#include "../WindowHandle/WindowHandle.h"

namespace Brokkr
{
	struct PushConstants
	{
		glm::mat4 objectMatrix = glm::identity<glm::mat4>();
	};

	struct MeshVertex
	{
		glm::vec3 position;
	};

    VulkanRenderer::VulkanRenderer(CoreSystems* pCoreManager)
        : CoreSubsystem(pCoreManager)
    {
    }

    void VulkanRenderer::Init(const std::string& argv, Brokkr::WindowHandle* pWindowHandle)
    {
        // Initialize Vulkan and shader library
        m_VulkanContext.Initialize(pWindowHandle->GetWindowName().c_str(), GAP311::VulkanWrapper::CreateVulkanSurfaceSDL(pWindowHandle->GetWindow()), {});
        m_ShaderLibrary.Initialize(m_VulkanContext.GetDevice(), {});

        CreatePipelines();
    }

    void VulkanRenderer::CreatePipelines()
    {

		vk::PolygonMode meshPolygonMode = vk::PolygonMode::eFill;
		vk::CullModeFlags meshCullMode = vk::CullModeFlagBits::eBack;
		vk::FrontFace meshFrontFace = vk::FrontFace::eCounterClockwise;
		bool meshDepthTestEnable = true;
		vk::CompareOp meshDepthCompareOp = vk::CompareOp::eLess;
		bool meshDepthWriteEnable = true;

		gridPipeline = vulkan.CreatePipeline(
			{
				.shaderPushConstants =
				{
					vk::PushConstantRange()
						.setOffset(0)
						.setSize(sizeof(PushConstants))
						.setStageFlags(vk::ShaderStageFlagBits::eAllGraphics)
				},
				.shaderUniforms =
				{
					cameraUniform,
				},
				.shaderStages =
				{
					vk::PipelineShaderStageCreateInfo()
						.setStage(vk::ShaderStageFlagBits::eVertex)
						.setPName("main")
						.setModule(shaderLib.GetModule("grid.vert")),
					vk::PipelineShaderStageCreateInfo()
						.setStage(vk::ShaderStageFlagBits::eFragment)
						.setPName("main")
						.setModule(shaderLib.GetModule("grid.frag"))
				},
				.polygonMode = vk::PolygonMode::eFill,
				.cullMode = vk::CullModeFlagBits::eNone,
				.frontFace = vk::FrontFace::eCounterClockwise,
				.depthTestEnable = true,
				.depthCompareOp = vk::CompareOp::eLess,
				.depthWriteEnable = false,
				.colorBlendStates = {
					vk::PipelineColorBlendAttachmentState()
						.setBlendEnable(true)
						.setColorBlendOp(vk::BlendOp::eAdd)
						.setSrcColorBlendFactor(vk::BlendFactor::eSrcAlpha)
						.setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha)
						.setAlphaBlendOp(vk::BlendOp::eAdd)
						.setSrcAlphaBlendFactor(vk::BlendFactor::eSrcAlpha)
						.setDstAlphaBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha)
						.setColorWriteMask(vk::ColorComponentFlagBits::eA | vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB)
				},
			});

		meshPipeline = vulkan.CreatePipeline(
			{
				.vertexBindings =
				{
					vk::VertexInputBindingDescription()
						.setBinding(0)
						.setInputRate(vk::VertexInputRate::eVertex)
						.setStride(sizeof(MeshVertex)),
				},
				.vertexAttributes =
				{
					vk::VertexInputAttributeDescription()
						.setLocation(0)
						.setBinding(0)
						.setFormat(vk::Format::eR32G32B32Sfloat)
						.setOffset(offsetof(MeshVertex, MeshVertex::position)),
				},
				.shaderPushConstants =
				{
					vk::PushConstantRange()
						.setOffset(0)
						.setSize(sizeof(PushConstants))
						.setStageFlags(vk::ShaderStageFlagBits::eAllGraphics)
				},
				.shaderUniforms =
				{
					cameraUniform,
				},
				.shaderStages =
				{
					vk::PipelineShaderStageCreateInfo()
						.setStage(vk::ShaderStageFlagBits::eVertex)
						.setPName("main")
						.setModule(shaderLib.GetModule("general.vert")),
					vk::PipelineShaderStageCreateInfo()
						.setStage(vk::ShaderStageFlagBits::eFragment)
						.setPName("main")
						.setModule(shaderLib.GetModule("general.frag"))
				},
				.polygonMode = meshPolygonMode,
				.cullMode = meshCullMode,
				.frontFace = meshFrontFace,
				.depthTestEnable = meshDepthTestEnable,
				.depthCompareOp = meshDepthCompareOp,
				.depthWriteEnable = meshDepthWriteEnable,

			/*.colorBlendStates =
			{
				vk::PipelineColorBlendAttachmentState()
					.setBlendEnable(true)
					.setColorBlendOp(vk::BlendOp::eAdd)
					.setSrcColorBlendFactor(vk::BlendFactor::eSrcAlpha)
					.setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha)
					.setAlphaBlendOp(vk::BlendOp::eAdd)
					.setSrcAlphaBlendFactor(vk::BlendFactor::eSrcAlpha)
					.setDstAlphaBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha)
					.setColorWriteMask(vk::ColorComponentFlagBits::eA | vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB)
			},*/
			});
    }
}
