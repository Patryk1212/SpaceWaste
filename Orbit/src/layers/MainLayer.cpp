#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
    std::cout << "MAIN Layer Attached" << std::endl;

    fileLoader.loadFileNames();
    fileLoader.loadTLEandCreateObjects(spaceObjects);

    std::cout << "Data Ready" << std::endl << std::endl << std::endl;
    
    
    // send object to graphis 
    // record cmd buffers
    

    //cameraController = std::make_unique<Engine::CameraController>();
    //cameraController->init(Engine::Application::get().getWindows());
}

void MainLayer::onUpdate(float deltaTime)
{

	// update objects' scale etc
    if (xd)
    {
        //Engine::Renderer3D::recordCommandBuffers(spaceObjects);
        xd = false;
    }
   // Engine::Renderer3D::updateFrame(spaceObjects);
    //Engine::Renderer3D::updateFrame(deltaTime, cameraController->getCamera());
}

void MainLayer::onRender()
{
}

bool MainLayer::onEvent(Engine::Event& event)
{


	return true;
}
