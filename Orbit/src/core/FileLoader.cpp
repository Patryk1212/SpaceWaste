#include "pch.h"
#include "FileLoader.h"

void FileLoader::loadFileNames()
{
    std::fstream file;
    file.open("files/filenames.txt", std::ios::in);

    if (file.good())
    {
        std::cout << "Loading file names:" << std::endl;

        std::string line;
        while (std::getline(file, line))
        {
            if (line == "") break;
            std::cout << line.c_str() << std::endl;
            fileNames.emplace_back(line);
        }
        
        std::cout << "Total number of files: " << fileNames.size() << std::endl;
    }

    file.close();
}

void FileLoader::loadTLEandCreateObjects(std::vector<std::unique_ptr<Engine::Object>>& objects)
{
    std::fstream file;

    for (const auto& name : fileNames)
    {
        file.open("files/" + name + ".txt", std::ios::in);

        if (file.good())
        {
            int number = 0;
            std::string name;
            std::string one;
            std::string two;

            std::string line;

            while (std::getline(file, line))
            {
                //std::cout << line.c_str() << std::endl;
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
                    std::unique_ptr<Engine::Object> object = std::make_unique<SpaceObject>(name, one, two);
                    objects.emplace_back(std::move(object));
                    number = 0;
                }
                else number++;
            }
        }

        file.close();
    }
}
