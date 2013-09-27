#include <featherkit/rendering/font.h>
#include <iostream>
#include <sstream>

namespace fea
{
    InvalidFontException::InvalidFontException(const std::string& message) : std::runtime_error(message)
    {
    }

    void Font::createFromPath(const std::string& path)
    {
        FILE* fp = fopen(path.c_str(), "rb");
        if(!fp)
        {
            std::cout << "errorperror!\n";
            exit(3);
        }

        fseek(fp, 0, SEEK_END);
        int datasize = (int)ftell(fp);
        fseek(fp, 0, SEEK_SET);
        unsigned char* data = (unsigned char*)malloc(datasize);
        if(data == NULL) 
        {
            std::cout << "perrorerror!\n";
            exit(3);
        }
        fread(data, 1, datasize, fp);
        fclose(fp);
        createFromData(data);
    }

    void Font::createFromData(uint8_t* fontData)
    {
        sth_create(512, 512); //will work once
        //sth_delete(); //must make static shared singleton out of it for now
        int32_t font = sth_add_font_from_memory(fontData);
        
        if(font != 0)
        {
            fontId = font;
        }
        else
        {
            std::stringstream ss;
            ss << "Error! While creating font!\n";
            throw(InvalidFontException(ss.str()));
        }
    }

    int32_t Font::getId() const
    {
        return fontId;
    }
}
