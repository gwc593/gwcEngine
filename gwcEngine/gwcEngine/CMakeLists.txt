cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)  # or newer
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_subdirectory("vendor/GLFW")
add_subdirectory("vendor/Glad")
add_subdirectory("vendor/tinyxml")

set(SRC  
    "src/gepch.cpp"
    "src/gwcEngine/Core/Log.cpp"
    "src/gwcEngine/Core/Time.cpp"
    "src/gwcEngine/Core/Input.cpp"
    "src/gwcEngine/Core/Layer.cpp"
    "src/gwcEngine/Core/Window.cpp"
    "src/gwcEngine/Core/FileSystem.cpp"
    "src/gwcEngine/Core/LayerStack.cpp"
    "src/gwcEngine/Core/application.cpp"
    "src/gwcEngine/ECS/ECS.cpp"
    "src/gwcEngine/ECS/Entity.cpp"
    "src/gwcEngine/ECS/System.cpp"
    "src/gwcEngine/ECS/Component.cpp"
    "src/gwcEngine/Events/Event.cpp"
    "src/gwcEngine/Events/EventCallback.cpp"
    "src/gwcEngine/Renderer/Shader/Buffer.cpp"
    "src/gwcEngine/Renderer/Shader/Shader.cpp"
    "src/gwcEngine/Renderer/Shader/IndexBuffer.cpp"
    "src/gwcEngine/Renderer/Shader/VertexArray.cpp"
    "src/gwcEngine/Renderer/Shader/VertexBuffer.cpp"
    "src/gwcEngine/Renderer/Shader/ShaderUniform.cpp"
    "src/gwcEngine/Renderer/Shader/UniformBuffer.cpp"
    "src/gwcEngine/Renderer/Shader/UniformBufferTypes.cpp"
    "src/gwcEngine/Renderer/Texture.cpp"
    "src/gwcEngine/Renderer/Renderer.cpp"
    "src/gwcEngine/Renderer/FrameBuffer.cpp"
    "src/gwcEngine/Renderer/RendererAPI.cpp"
    "src/gwcEngine/Renderer/RenderCommand.cpp"
    "src/gwcEngine/Debugging/Profiling/Instrumentor.cpp"
    "src/gwcEngine/Components/System/Panel.cpp"
    "src/gwcEngine/Components/System/Cursor.cpp"
    "src/gwcEngine/Components/Cameras/Camera.cpp"
    "src/gwcEngine/Components/Cameras/PerspectiveCamera.cpp"
    "src/gwcEngine/Components/Cameras/OrthographicCamera.cpp"
    "src/gwcEngine/Components/Physics/Ray.cpp"
    "src/gwcEngine/Components/Physics/Sphere.cpp"
    "src/gwcEngine/Components/Physics/LifeTime.cpp"
    "src/gwcEngine/Components/Physics/Transform.cpp"
    "src/gwcEngine/Components/Renderable/Mesh.cpp"
    "src/gwcEngine/Components/Renderable/Material.cpp"
    "src/gwcEngine/Components/Renderable/RenderLayer.cpp"
    "src/gwcEngine/AssetManagment/ModelLoader.cpp"
    "vendor/stb_image/stb_image.cpp"
    )

add_definitions("-DGLEW_STATIC" "-DGE_BUILD_DLL" "-DGLFW_INCLUDE_NONE" "-DTIXML_USE_STL")

link_directories("")

include_directories("src"
    "src/gwcEngine/Core"
    "src/gwcEngine/AssetManagment"
    "src/gwcEngine/Components"
    "src/gwcEngine/Debugging"
    "src/gwcEngine/Renderer"
    "src/gwcEngine/Renderer/Shader"
    "src/gwcEngine/Events"
    "src/gwcEngine/ECS"
    "vendor/spdlog/include"
    "vendor/tinyxml"
    "vendor/GLFW/include"
    "vendor/Glad/include"
    "vendor/glm"
    "vendor/stb_image")

add_library(gwcEngine STATIC ${SRC})
#target_precompile_headers(gwcEngine PRIVATE "src/gepch.h")
target_compile_options(gwcEngine PRIVATE -save-temps=obj)
target_link_libraries(gwcEngine "GLFW" "Glad" "GL" "tinyxml" "pthread" "X11" "Xrandr" "Xi" "dl")
