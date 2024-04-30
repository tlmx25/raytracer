/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** builder
*/

#include "builder.hpp"
#include "material.hpp"

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

std::map<std::string, shared_ptr<IMaterial>> Builder::getMaterials()
{
    std::map<std::string, shared_ptr<IMaterial>> materials;
    const libconfig::Setting &root = _cfg.getRoot();
    const libconfig::Setting &materials_cfg = root["materials"];
    int count = materials_cfg.getLength();

    for (int i = 0; i < count; i++) {
        const libconfig::Setting &material = materials_cfg[i];
        std::string name = material.getName();
        std::string type;
        shared_ptr<IMaterial> mat;
        if (!material.exists("type") || !material.lookupValue("type", type)) {
            std::cerr << "Builder: error on reading material." << std::endl;
            throw std::runtime_error("Builder: error on reading material.");
        }
        if (type == "lambertian") {

            mat = std::make_shared<Lambertian>(material);
        }
        materials[name] = mat;
    }
    return materials;
}
