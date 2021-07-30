#include "TextureHolder.hpp"

#include <list>
#include <filesystem>

void TextureHolder::load(const std::string_view folder)
{
    std::list<std::filesystem::path> file_pathes;

    for (auto& file : std::filesystem::recursive_directory_iterator(folder))
        file_pathes.emplace_back(file.path());

    for (const auto& path : file_pathes)
    {
        sf::Texture texture;
        texture.loadFromFile(path.string());

        m_textures.emplace(path.stem().string(), texture);
    }
}

sf::Texture* TextureHolder::get(const std::string& name)
{
    if (auto found = m_textures.find(name); found != m_textures.end())
        return &found->second;

    return nullptr;
}
