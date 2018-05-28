#include "loader.hpp"

namespace core
{
    void loadOBJ(std::string path)
    {
        std::ifstream src(path);

        if (!src)
        {
            std::cout << "Unable to locate model at " << path << std::endl;
            exit(1);
        }

        std::string line;

        while (std::getline(src, line))
        {

        }
    }
}