#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
    /* add earth */
    glm::vec3 earthPos{ 0.0f, 0.0f, 0.0f };
    glm::vec3 earthSize{ 600.0f, 600.0f, 600.0f };
    glm::vec3 earthColor{ 0.05f, 0.82f, 0.1f };
    std::unique_ptr<Engine::Object> earth = std::make_unique<SpaceObject>(earthPos, earthSize, earthColor);
    spaceObjects.emplace_back(std::move(earth));
    /* --------- */

    fileLoader.loadFileNames();
    fileLoader.loadTLEandCreateObjects(spaceObjects);

    Engine::Renderer3D::recordCommandBuffers(spaceObjects);   
    
    //CString  szResult[2];
    //data = std::make_unique<CSpaceTrackDownload>(L"https://www.space-track.org/ajaxauth/login", L"ostrpatryk@gmail.com", L"T6RkviN94d!N_ra");
    //
    //
    //szResult[0] = data->Query(L"/basicspacedata/query/class/tle_latest/orderby/TLE_LINE0%20asc/limit/50/format/3le/metadata/false/favorites/Human_Spaceflight");
    //szResult[1] = data->Query(L"/basicspacedata/query/class/tle_latest/orderby/TLE_LINE0%20asc/limit/50/format/3le/metadata/false/favorites/Amateur");

    Engine::Message message;
    message.id = 0;
    message.objects = spaceObjects;
    message.intNumber = spaceObjects.size();
    uiLayerHandle->receiveMessage(message);
}

void MainLayer::onUpdate(float deltaTime)
{

    //static auto startTime = std::chrono::high_resolution_clock::now();
    //
    //auto currentTime = std::chrono::high_resolution_clock::now();
    //float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    cameraController->onUpdate(spaceObjects[currentObjectOnFocus]->getPos());

    //float x_pos = cameraController->getWindowHandle()->getMouseX();
    //float y_pos = cameraController->getWindowHandle()->getMouseY();
    //
    //glm::mat4 proj = cameraController->getCamera()->getProjectionMatrix();
    //glm::mat4 view = cameraController->getCamera()->getViewMatrix();
    //
    //glm::mat4 result = proj * view;
    //
    //glm::mat4 result_in = glm::inverse(result);
    //
    //glm::vec4 mouse;
    //mouse.x = (2.0f * x_pos) / 1280.f - 1.0f;
    //mouse.y = 1.f - (2.0f * y_pos) / 720.f;
    //mouse.z = 1.f;// 2.f * 10000.f - 0.1f;
    //mouse.w = 1.f;
    //
    //glm::vec4 final = mouse * result_in;
    //
    ////final.x /= final.w;
    ////final.y /= final.w;
    ////final.z /= final.w;
    //
    ////glm::normalize(final);
    //system("cls");
    //
    //final2 = { mouse.x * cameraController->getCurrentZoom(), final.y * cameraController->getCurrentZoom(), final.z * cameraController->getCurrentZoom() };
    //
    //std::cout << "X " << final2.x  << std::endl;
    //std::cout << "Y " << final2.y  << std::endl;
    //std::cout << "Z " << final2.z  << std::endl;
   

    updateObjectsPosition(deltaTime);
    
    Engine::Renderer3D::updateFrame(spaceObjects);
}

void MainLayer::onRender()
{
}

void MainLayer::passCamera(std::unique_ptr<Engine::CameraController>& cc)
{
    cameraController = std::move(cc);
}

bool MainLayer::onEvent(Engine::Event& event)
{
    objectsResizeZoom(event);

    Engine::MouseButtonPressedEvent& e = (Engine::MouseButtonPressedEvent&)event;
    
    //if (e.getEventType() == Engine::EventType::MOUSE_PRESSED)
    //{
    //    Engine::Message message;
    //    message.number.push_back(12);
    //    uiLayerHandle->receiveMessage(message);
    //}

    //if (e.getEventType() == Engine::EventType::MOUSE_PRESSED)
    //{
    //    for (const auto& sp : spaceObjects)
    //    {
    //        if (sp->checkInside(final2))
    //        {
    //            sp->setScale({ 30.f, 30.f, 30.f });
    //            std::cout << "Inside" << std::endl;
    //            break;
    //        }
    //
    //    }
    //}

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
    for (int i = 0; i < spaceObjects.size(); i++)// auto& cube : spaceObjects)
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
            spaceObjects[i]->getUniformbufferObject().color = highLightColor;
        }
        else spaceObjects[i]->getUniformbufferObject().color = spaceObjects[i]->getColor();

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
