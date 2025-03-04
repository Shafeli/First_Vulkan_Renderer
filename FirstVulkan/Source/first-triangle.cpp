
#include <functional>

#include "../gap-311/VulkanShaderLibrary.hpp"
#include "../gap-311/VulkanWrapper.hpp"

#define EXAMPLE_GENERATE_IN_VERTEX_SHADER 0
#define EXAMPLE_USE_VERTEX_BUFFER 1

using namespace GAP311;

using TickFunc = std::function<void(float)>;
using ShutdownFunc = std::function<void()>;

bool ApplicationMain(SDL_Rect windowRect, SDL_Window* pWindow, VulkanWrapper& vulkan, VulkanShaderLibrary& shaderLib,
	std::function<void(ShutdownFunc, TickFunc)>& runApplication)
{
#if EXAMPLE_GENERATE_IN_VERTEX_SHADER
	const GraphicsPipelineConfig pipelineConfig =
	{
		.shaderStages =
		{
			vk::PipelineShaderStageCreateInfo()
				.setStage(vk::ShaderStageFlagBits::eVertex)
				.setPName("main")
				.setModule(shaderLib.GetModule("triangle_hardcoded.vert")),
			vk::PipelineShaderStageCreateInfo()
				.setStage(vk::ShaderStageFlagBits::eFragment)
				.setPName("main")
				.setModule(shaderLib.GetModule("vertex_color.frag"))
		},
	};
#endif
#if EXAMPLE_USE_VERTEX_BUFFER

	// Source https://www.geogebra.org/geometry?lang=en gave up and this calulator helped mapping out the vertex
	constexpr float positions[] = 
	{
		// H
		-0.9f,  0.5f,  -0.9f, -0.5f,  -0.85f, -0.5f,
		-0.9f,  0.5f,  -0.85f, -0.5f,  -0.85f,  0.5f,

		// H
		-0.75f,  0.5f,  -0.75f, -0.5f,  -0.7f, -0.5f,
		-0.75f,  0.5f,  -0.7f, -0.5f,  -0.7f,  0.5f,

		// H
		-0.9f,  0.05f,  -0.7f,  0.05f,  -0.7f, -0.05f,
		-0.9f,  0.05f,  -0.7f, -0.05f,  -0.9f, -0.05f,

		// E
		-0.625f,  0.5f,  -0.625f, -0.5f,  -0.575f, -0.5f,
		-0.625f,  0.5f,  -0.575f, -0.5f,  -0.575f,  0.5f,

		// E
		-0.625f,  0.5f,  -0.475f,  0.5f,  -0.475f,  0.45f,
		-0.625f,  0.5f,  -0.475f,  0.45f,  -0.625f,  0.45f,

		// E
		-0.625f,  0.05f,  -0.525f,  0.05f,  -0.525f, -0.05f,
		-0.625f,  0.05f,  -0.525f, -0.05f,  -0.625f, -0.05f,

		// E
		-0.625f, -0.5f,  -0.475f, -0.5f,  -0.475f, -0.45f,
		-0.625f, -0.5f,  -0.475f, -0.45f,  -0.625f, -0.45f,

		// L
		-0.45f,  0.5f,  -0.45f, -0.5f,  -0.4f, -0.5f,
		-0.45f,  0.5f,  -0.4f, -0.5f,  -0.4f,  0.5f,

		// L
		-0.45f, -0.5f,  -0.3f, -0.5f,  -0.3f, -0.45f,
		-0.45f, -0.5f,  -0.3f, -0.45f,  -0.45f, -0.45f,

		// L
		-0.275f,  0.5f,  -0.275f, -0.5f,  -0.225f, -0.5f,
		-0.275f,  0.5f,  -0.225f, -0.5f,  -0.225f,  0.5f,

		// L
		-0.275f, -0.5f,  -0.125f, -0.5f,  -0.125f, -0.45f,
		-0.275f, -0.5f,  -0.125f, -0.45f,  -0.275f, -0.45f,
		 
		// O
		-0.1f,  0.5f,  -0.1f, -0.5f,  -0.05f, -0.5f,
		-0.1f,  0.5f,  -0.05f, -0.5f,  -0.05f,  0.5f,

		// O
		0.1f,  0.5f,  0.1f, -0.5f,  0.05f, -0.5f,
		0.1f,  0.5f,  0.05f, -0.5f,  0.05f,  0.5f,

		// O
		-0.1f,  0.5f,  0.1f,  0.5f,  0.1f,  0.45f,
		-0.1f,  0.5f,  0.1f,  0.45f,  -0.1f,  0.45f,

		// O
		-0.1f, -0.5f,  0.1f, -0.5f,  0.1f, -0.45f,
		-0.1f, -0.5f,  0.1f, -0.45f,  -0.1f, -0.45f
	};

	constexpr float colors[] = 
	{
		// H
		1.0f, 0.0f, 0.0f, // red
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		// H
		1.0f, 0.0f, 0.0f, // red
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 

		// H
		1.0f, 0.0f, 0.0f, // Red
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 

		// E
		0.0f, 1.0f, 0.0f, // Green
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 

		// E
		0.0f, 1.0f, 0.0f, // Green
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 

		// E
		0.0f, 1.0f, 0.0f, // Green
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 

		// E
		0.0f, 1.0f, 0.0f, // Green
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		// L
		0.0f, 0.0f, 1.0f, // Blue
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 

		// L
		0.0f, 0.0f, 1.0f, // Blue
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		// L
		1.0f, 0.0f, 1.0f, // Purple
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		// L
		1.0f, 0.0f, 1.0f, // Purple
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		// O
		1.0f, 1.0f, 0.0f, // Yellow
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,

	    // O
		1.0f, 1.0f, 0.0f, // Yellow
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 

		// O
		1.0f, 1.0f, 0.0f, // Yellow
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,

		// O
		1.0f, 1.0f, 0.0f, // Yellow
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		// O
		1.0f, 1.0f, 0.0f, // Yellow
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f

	};

	vk::Buffer positionsBuffer = vulkan.CreateBuffer(vk::BufferUsageFlagBits::eVertexBuffer, sizeof(positions), positions);
	vk::Buffer colorsBuffer = vulkan.CreateBuffer(vk::BufferUsageFlagBits::eVertexBuffer, sizeof(colors), colors);

	const GraphicsPipelineConfig pipelineConfig =
	{
		.vertexBindings =
		{
			vk::VertexInputBindingDescription()
				.setBinding(0)
				.setInputRate(vk::VertexInputRate::eVertex)
				.setStride(sizeof(positions[0]) * 2),
			vk::VertexInputBindingDescription()
				.setBinding(1)
				.setInputRate(vk::VertexInputRate::eVertex)
				.setStride(sizeof(colors[0]) * 3),
		},
		.vertexAttributes =
		{
			vk::VertexInputAttributeDescription()
				.setLocation(0)
				.setBinding(0)
				.setFormat(vk::Format::eR32G32Sfloat)
				.setOffset(0),
			vk::VertexInputAttributeDescription()
				.setLocation(1)
				.setBinding(1)
				.setFormat(vk::Format::eR32G32B32Sfloat)
				.setOffset(0),
		},
		.shaderStages =
		{
			vk::PipelineShaderStageCreateInfo()
				.setStage(vk::ShaderStageFlagBits::eVertex)
				.setPName("main")
				.setModule(shaderLib.GetModule("vertex_color.vert")),
			vk::PipelineShaderStageCreateInfo()
				.setStage(vk::ShaderStageFlagBits::eFragment)
				.setPName("main")
				.setModule(shaderLib.GetModule("vertex_color.frag"))
		},
	};
#endif
    std::shared_ptr<VulkanWrapper::GraphicsPipeline> pipeline = vulkan.CreatePipeline(pipelineConfig);

	runApplication(
		[&]()
		{
			vulkan.DestroyPipeline(pipeline);

#if EXAMPLE_USE_VERTEX_BUFFER
			if (positionsBuffer)
				vulkan.DestroyBuffer(positionsBuffer);
			if (colorsBuffer)
				vulkan.DestroyBuffer(colorsBuffer);
#endif
		},
		[&](float tickDelta)
		{
			vk::CommandBuffer commands;
			vk::Framebuffer framebuffer;
			if (!vulkan.BeginFrame(commands, framebuffer))
				return;

			vk::ClearValue clearValues[] =
			{
				vk::ClearColorValue(0.05f, 0.05f, 0.05f, 0.0f),
			};

			vk::RenderPassBeginInfo rpbi{};
			rpbi.setRenderPass(vulkan.GetDisplayRenderPass());
			rpbi.setFramebuffer(framebuffer);
			rpbi.setClearValues(clearValues);
			rpbi.setRenderArea(vk::Rect2D({ 0, 0 }, { static_cast<uint32_t>(windowRect.w), static_cast<uint32_t>(windowRect.h) }));
			commands.beginRenderPass(rpbi, vk::SubpassContents::eInline);

#if EXAMPLE_USE_VERTEX_BUFFER
			commands.bindVertexBuffers(0, { positionsBuffer, colorsBuffer }, { 0, 0 });
#endif
			commands.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline->GetPipeline());

			// 18+24+12+12+24=90 vertices
			commands.draw(90, 1, 0, 0);

			commands.endRenderPass();
			vulkan.EndFrame();
		}
	);

	return true;
}

int main(int argc, char* argv[])
{
	const char* appName = argv[0];

	if (0 > SDL_Init(SDL_INIT_VIDEO))
		return -1;

	SDL_Rect windowRect = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };

	SDL_Window* pSDLWindow = SDL_CreateWindow(appName, windowRect.x, windowRect.y, windowRect.w, windowRect.h, SDL_WINDOW_VULKAN);
	if (!pSDLWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	VulkanWrapper vulkan;
	VulkanWrapper::ConfigOptions options{};
	options.configureInstanceFunc = [](vkb::InstanceBuilder& builder) -> bool
	{
		builder.require_api_version(1, 3);
		return true;
	};
	options.debugLogFunc = VulkanWrapper::VulkanLogToSDL();
	if (!vulkan.Initialize(appName, VulkanWrapper::CreateVulkanSurfaceSDL(pSDLWindow), options))
	{
		SDL_Log("Failed initializing VulkanWrapper.");
		SDL_DestroyWindow(pSDLWindow);
		SDL_Quit();
		return -1;
	}

	VulkanShaderLibrary shaderLib;
	VulkanShaderLibrary::ConfigOptions shaderOptions{};
	shaderOptions.logMessage = [](const char* msg)
		{
			SDL_Log("ShaderLibrary: %s", msg);
		};
	shaderOptions.searchDirs = {
		std::filesystem::current_path().string(), // working dir
		std::filesystem::path(argv[0]).parent_path().string(), // exe dir
		std::filesystem::relative(std::filesystem::path(__FILE__).parent_path()).string(), // source file dir
	};
	if (!shaderLib.Initialize(vulkan.GetDevice(), shaderOptions))
	{
		SDL_Log("Failed initializing VulkanShaderLibrary.");
		vulkan.Shutdown();
		SDL_DestroyWindow(pSDLWindow);
		SDL_Quit();
		return -1;
	}

	std::function runApp = [&](ShutdownFunc appShutdown, TickFunc appTick)
		{
			const uint64_t timerFreq = SDL_GetPerformanceFrequency();
			uint64_t timerLastTicks = SDL_GetPerformanceCounter();
			float deltaTime = 0;
			
			bool shutdownRequested = false;
			while (!shutdownRequested)
			{
				SDL_Event event;
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						shutdownRequested = true;
				}

				appTick(deltaTime);

				uint64_t timerNow = SDL_GetPerformanceCounter();
				deltaTime = float(double(timerNow - timerLastTicks) / timerFreq);
				timerLastTicks = timerNow;
			}

			vulkan.GetDevice().waitIdle();
			appShutdown();
		};

	bool result = ApplicationMain(windowRect, pSDLWindow, vulkan, shaderLib, runApp);
	if (!result)
	{
		SDL_Log("Application indicated failure.");
	}

	shaderLib.Shutdown();
	vulkan.Shutdown();
	SDL_DestroyWindow(pSDLWindow);
	SDL_Quit();
	return result ? 0 : -1;
}
