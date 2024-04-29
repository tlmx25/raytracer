/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** builder
*/

#include "builder.hpp"

Builder::Builder(const char *path)
{
    try {
        _cfg.readFile(path);
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Builder: error on reading file." << std::endl;
        throw fioex;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parsing error  " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        throw libconfig::ParseException(pex);
    }
}

Builder::Builder(std::string path)
{
    try {
        _cfg.readFile(path.c_str());
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Builder: error on reading file." << std::endl;
        throw fioex;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parsing error  " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        throw libconfig::ParseException(pex);
    }
}
