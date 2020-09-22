#include "include\FileTranslator.h"
#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

FileTranslator::FileTranslator(std::vector<Zone> ZONES)
{
    this->ZONES = ZONES;
    ZONES_Size = ZONES.size();
}

void FileTranslator::MapIntoFile (const char* MapName)
{
    std::ofstream MapCreationFile(MapName);
    std::string OutputData = GenerateMapString();
    for(unsigned int i = 0; i<OutputData.size(); i++)
    {
        std::cout<<OutputData[i];
        MapCreationFile<<OutputData[i];
    }
}
std::string FileTranslator::GenerateMapString ()
{
    std::string OutputString = "";
    char* tempNumber = nullptr;
    for(unsigned int i = 0; i<ZONES.size(); i++)
    {
        OutputString += ZONES[i].getZoneType();
        OutputString += " ";
        OutputString += std::to_string(ZONES[i].getLeftDownVertex().x);
        OutputString += " ";
        OutputString += std::to_string(ZONES[i].getLeftDownVertex().y);
        OutputString += " ";
        OutputString += std::to_string(ZONES[i].getRightUpVertex().x);
        OutputString += " ";
        OutputString += std::to_string(ZONES[i].getRightUpVertex().y);
        OutputString += "\n";
    }
    return OutputString;
}
FileTranslator::~FileTranslator()
{
    //dtor
}
