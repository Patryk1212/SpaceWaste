#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
    std::cout << "MAIN Layer Attached" << std::endl;

    /* add earth */
    glm::vec3 earthPos{ 0.0f, 0.0f, 0.0f };
    glm::vec3 earthSize{ 250.0f, 250.0f, 250.0f };
    glm::vec3 earthColor{ 0.23f, 0.7f, 0.44f };
    std::unique_ptr<Engine::Object> earth = std::make_unique<SpaceObject>(earthPos, earthSize, earthColor);
    spaceObjects.emplace_back(std::move(earth));
    /* --------- */

    fileLoader.loadFileNames();
    fileLoader.loadTLEandCreateObjects(spaceObjects);

    std::cout << "Data Ready" << std::endl;
    std::cout << "Objects loaded: ";
    std::cout << spaceObjects.size() << std::endl << std::endl;

    Engine::Renderer3D::recordCommandBuffers(spaceObjects);   

    //cameraController = std::make_unique<Engine::CameraController>();
    //cameraController->init(Engine::Application::get().getWindows());
}

void MainLayer::onUpdate(float deltaTime)
{

    //static auto startTime = std::chrono::high_resolution_clock::now();
    //
    //auto currentTime = std::chrono::high_resolution_clock::now();
    //float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    cameraController->onUpdate();

   

    updateObjectsPosition();
    
    Engine::Renderer3D::updateFrame(spaceObjects);
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
    objectsResizeZoom(event);
	return true;
}

void MainLayer::updateObjectsPosition()
{
    for (const auto& cube : spaceObjects)
    {
        cube->getUniformbufferObject().view = cameraController->getCamera()->getViewMatrix();
        cube->getUniformbufferObject().proj = cameraController->getCamera()->getProjectionMatrix();

        cube->getUniformbufferObject().model = glm::translate(glm::mat4(1.0f), cube->getPos());
        //cube->ubo.model *= glm::rotate(glm::mat4(1.0f), time * glm::radians(cube->rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        cube->getUniformbufferObject().model = glm::scale(cube->getUniformbufferObject().model, cube->getScale());
        cube->getUniformbufferObject().color = cube->getColor(); // not every frame
    }
}

void MainLayer::objectsResizeZoom(Engine::Event& event)
{
    float oldZoom = cameraController->getCurrentZoom();
    if (cameraController->onEvent(event))
    {
        float newZoom = cameraController->getCurrentZoom();
        newZoom -= oldZoom;

        if (newZoom < 0) // zoom in
        {
            for (int i = 1; i < spaceObjects.size(); i++)
            {
                spaceObjects[i]->resize(ZOOM_IN);
            }
        }
        else if (newZoom > 0) // zoom out
        {
            for (int i = 1; i < spaceObjects.size(); i++)
            {
                spaceObjects[i]->resize(ZOOM_OUT);
            }
        }
    }
}
