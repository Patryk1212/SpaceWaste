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
    
    //CString  szResult[2];
    //data = std::make_unique<CSpaceTrackDownload>(L"https://www.space-track.org/ajaxauth/login", L"ostrpatryk@gmail.com", L"T6RkviN94d!N_ra");
    //
    //
    //szResult[0] = data->Query(L"/basicspacedata/query/class/tle_latest/orderby/TLE_LINE0%20asc/limit/50/format/3le/metadata/false/favorites/Human_Spaceflight");
    //szResult[1] = data->Query(L"/basicspacedata/query/class/tle_latest/orderby/TLE_LINE0%20asc/limit/50/format/3le/metadata/false/favorites/Amateur");
}

void MainLayer::onUpdate(float deltaTime)
{

    //static auto startTime = std::chrono::high_resolution_clock::now();
    //
    //auto currentTime = std::chrono::high_resolution_clock::now();
    //float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    cameraController->onUpdate();

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
    //cameraController = std::make_unique<Engine::CameraController>();
    cameraController = std::move(cc);
}

bool MainLayer::onEvent(Engine::Event& event)
{
    objectsResizeZoom(event);

    Engine::MouseButtonPressedEvent& e = (Engine::MouseButtonPressedEvent&)event;
    
    if (e.getEventType() == Engine::EventType::MOUSE_PRESSED)
    {
        Engine::Message message;
        message.number.push_back(12);
        uiLayerHandle->receiveMessage(message);
    }

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
    std::cout << "Main Layer received message" << std::endl;
}

void MainLayer::updateObjectsPosition(float deltaTime)
{
    bool earth = true;
    for (const auto& cube : spaceObjects)
    {
        if (!earth)
        {
            cube->onUpdate(deltaTime);
        }

        cube->getUniformbufferObject().view = cameraController->getCamera()->getViewMatrix();
        cube->getUniformbufferObject().proj = cameraController->getCamera()->getProjectionMatrix();

        cube->getUniformbufferObject().model = glm::translate(glm::mat4(1.0f), cube->getPos());
        //cube->ubo.model *= glm::rotate(glm::mat4(1.0f), time * glm::radians(cube->rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        cube->getUniformbufferObject().model = glm::scale(cube->getUniformbufferObject().model, cube->getScale());
        cube->getUniformbufferObject().color = cube->getColor(); // not every frame

        earth = false;
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
