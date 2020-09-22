#ifndef FILETRANSLATOR_H
#define FILETRANSLATOR_H

#include "Zone.h"
#include <vector>

class FileTranslator
{
    public:
        FileTranslator(std::vector<Zone> ZONES);
        void MapIntoFile (const char* MapName);
        std::string GenerateMapString ();
        virtual ~FileTranslator();

    protected:

    private:
        std::vector<Zone> ZONES;
        unsigned int ZONES_Size;
        const int NumberSystem = 10;
};

#endif // FILETRANSLATOR_H
