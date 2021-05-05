#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
    /* add earth */
    glm::vec3 earthPos{ 0.0f, 0.0f, 0.0f };
    glm::vec3 earthSize{ 600.0f, 600.0f, 600.0f };
    glm::vec3 earthColor{ 0.05f, 0.60f, 0.1f };
    std::unique_ptr<Engine::Object> earth = std::make_unique<SpaceObject>(earthPos, earthSize, earthColor);
    spaceObjects.emplace_back(std::move(earth));
    /* --------- */

    fileLoader.loadFileNames();
    fileLoader.loadTLEandCreateObjects(spaceObjects);

    Engine::Renderer3D::recordCommandBuffers(spaceObjects);   
    
    Engine::Message message;
    message.id = 0;
    message.objects = spaceObjects;
    message.intNumber = spaceObjects.size();
    uiLayerHandle->receiveMessage(message);
}

void MainLayer::onUpdate(float deltaTime)
{
    cameraController->onUpdate(spaceObjects[currentObjectOnFocus]->getPos());   

    updateObjectsPosition(deltaTime);
    
    Engine::Renderer3D::updateFrame(spaceObjects);
}

void MainLayer::passCamera(std::unique_ptr<Engine::CameraController>& cc)
{
    cameraController = std::move(cc);
}

bool MainLayer::onEvent(Engine::Event& event)
{
    objectsResizeZoom(event);

    Engine::MouseButtonPressedEvent& e = (Engine::MouseButtonPressedEvent&)event;
    
	return true;
}

void MainLayer::setObserver(std::shared_ptr<Layer>& observer)
{
    uiLayerHandle = observer;
}

void MainLayer::receiveMessage(const Engine::Message& message)
{
    if (message.id == 0)
    {
        visSpeed = message.intNumber;
        running = message.status;
    }
    else if (message.id == 1)
    {
        currentObjectOnFocus = message.intNumber;
    }
}

void MainLayer::updateObjectsPosition(float deltaTime)
{
    // bool earth = true;
    for (int i = 0; i < spaceObjects.size(); i++)
    {
        if (i != 0 && running)
        {
            spaceObjects[i]->onUpdate(deltaTime, visSpeed);
        }

        spaceObjects[i]->getUniformbufferObject().view = cameraController->getCamera()->getViewMatrix();
        spaceObjects[i]->getUniformbufferObject().proj = cameraController->getCamera()->getProjectionMatrix();

        spaceObjects[i]->getUniformbufferObject().model = glm::translate(glm::mat4(1.0f), spaceObjects[i]->getPos());
        spaceObjects[i]->getUniformbufferObject().model = glm::scale(spaceObjects[i]->getUniformbufferObject().model, spaceObjects[i]->getScale());
        
        if (i != 0 && currentObjectOnFocus == i)
        {
            glm::vec3 highLightColor{ 0.f, 1.f, 0.f };
            spaceObjects[i]->setColor(highLightColor);
        }

        spaceObjects[i]->getUniformbufferObject().color = spaceObjects[i]->getColor();
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
