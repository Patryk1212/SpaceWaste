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

    float x_pos = cameraController->getWindowHandle()->getMouseX();
    float y_pos = cameraController->getWindowHandle()->getMouseY();

    glm::mat4 proj = cameraController->getCamera()->getProjectionMatrix();
    glm::mat4 view = cameraController->getCamera()->getViewMatrix();

    glm::mat4 result = proj * view;

    glm::mat4 result_in = glm::inverse(result);

    glm::vec4 mouse;
    mouse.x = (2.0f * x_pos) / 1280.f - 1.0f;
    mouse.y = 1.f - (2.0f * y_pos) / 720.f;
    mouse.z = 2.f * 10000.f - 0.1f;
    mouse.w = 1.f;

    glm::vec4 final = mouse;// *result_in;
    final2 = { final.x, final.y, final.z };
    //final.w = 1.0 / final.w;
    //
    //final.x *= final.w;
    //final.y *= final.w;
    //final.z *= final.w;

    system("cls");
    std::cout << "X " << mouse.x * cameraController->getCurrentZoom() << std::endl;
    std::cout << "Y " << mouse.y * cameraController->getCurrentZoom() << std::endl;
    //std::cout << "Z " << mouse.z * cameraController->getCurrentZoom() << std::endl;

   //glm::vec4 near = glm::vec4((x_pos - 640) / 640, -1 * (y_pos - 360) / 360, -1, 1.0);
   //glm::vec4 far = glm::vec4((x_pos - 640) / 640, -1 * (y_pos - 360) / 360, 1, 1.0);
   //glm::vec4 nearResult = result_in * near;
   //glm::vec4 farResult = result_in * far;
   //nearResult /= nearResult.w;
   //farResult /= farResult.w;
   //glm::vec3 dir = glm::vec3(farResult - nearResult);
   //glm::normalize(dir);

    //std::cout << "W " << final.w << std::endl;

   

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

    Engine::MouseButtonPressedEvent& e = (Engine::MouseButtonPressedEvent&)event;
    
    if (e.getEventType() == Engine::EventType::MOUSE_PRESSED)
    {
        for (const auto& sp : spaceObjects)
        {
            if (sp->checkInside(final2))
            {
                sp->setScale({ 30.f, 30.f, 30.f });
                std::cout << "Inside" << std::endl;
                break;
            }

        }
    }

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
