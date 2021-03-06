#include "pch.h"
#include "FileLoader.h"

void FileLoader::createObjectsAndLoadTLE(std::vector<std::unique_ptr<SpaceObject>>& objects)
{
    std::fstream file;
    file.open("files/SCORE.txt", std::ios::in);

    if (file.good())
    {
        int number = 0;
        std::string name;
        std::string one;
        std::string two;

        std::string line;

        while (std::getline(file, line)) 
        {            
           // std::cout << line.c_str() << std::endl;

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
                std::unique_ptr<SpaceObject> object = std::make_unique<SpaceObject>(name, one, two);
                std::cout << object->showName() << std::endl;
                objects.emplace_back(std::move(object));
                number = 0;
            }
            else number++;
        }
    }
   
    file.close();
}
