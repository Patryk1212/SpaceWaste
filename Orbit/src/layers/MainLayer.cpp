#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
    std::cout << "MAIN Layer Attached" << std::endl;

    /* add earth */
    glm::vec3 earthPos{ 0.0f, 0.0f, 0.0f };
    std::unique_ptr<Engine::Object> earth = std::make_unique<SpaceObject>(earthPos);
    spaceObjects.emplace_back(std::move(earth));

    fileLoader.loadFileNames();

    //for (int i = 0; i < 15; i++)
    fileLoader.loadTLEandCreateObjects(spaceObjects);

    std::cout << "Data Ready" << std::endl << std::endl << std::endl;
    
    Engine::Renderer3D::recordCommandBuffers(spaceObjects);
    // send object to graphis 
    // record cmd buffers
    

    //cameraController = std::make_unique<Engine::CameraController>();
    //cameraController->init(Engine::Application::get().getWindows());
}

void MainLayer::onUpdate(float deltaTime)
{
    cameraController->onUpdate();
    
    Engine::Renderer3D::updateFrame(spaceObjects, cameraController->getCamera());
    //Engine::Renderer3D::updateFrame(deltaTime, cameraController->getCamera());
}

void MainLayer::onRender()
{
}

void MainLayer::passCamera(std::unique_ptr<Engine::CameraController>& cc)
{
    //cameraController = std::make_unique<Engine::CameraController>();
    cameraController = std::move(cc);
}

bool MainLayer::onEvent(Engine::Event& event)
{
    cameraController->onEvent(event);

	return true;
}
