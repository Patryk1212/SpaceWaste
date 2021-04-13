#include "pch.h"
#include "FileLoader.h"

void FileLoader::loadFileNames()
{
    std::fstream file;
    file.open("files/filenames.txt", std::ios::in);

    if (file.good())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line == "") break;
            fileNames.emplace_back(line);
        }
    }

    file.close();
}

void FileLoader::loadTLEandCreateObjects(std::vector<std::shared_ptr<Engine::Object>>& objects)
{
    std::fstream file;

    int x = 0;

    for (const auto& name : fileNames)
    {
        file.open("files/" + name + ".txt", std::ios::in);

        if (file.good())
        {
            int number = -1;
            std::string type;
            std::string name;
            std::string one;
            std::string two;

            std::string line;

            while (std::getline(file, line))
            {
                if (number == -1)
                {
                    type = line;
                    number++;
                }
                else
                {
                    switch (number)
                    {
                    case 0:
                    {
                        name = line;
                        break;
                    }
                    case 1:
                    {
                        one = line;
                        break;
                    }
                    case 2:
                    {
                        two = line;
                        break;
                    }
                    default: break;
                    }

                    if (number == 2)
                    {
                        std::unique_ptr<Engine::Object> object = std::make_unique<SpaceObject>(name, one, two, type);
                        objects.emplace_back(std::move(object));
                        number = 0;
                        x++;
                    }
                    else number++;

                    if (x > 17381)
                    {
                        x = 0;
                        break;
                    }
                }
            }
        }

        file.close();
    }    
}
