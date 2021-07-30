#include "TextureHolder.hpp"

#include <list>
#include <filesystem>

void TextureHolder::load(const std::string_view folder)
{
    std::list<std::string> file_pathes;

    for (auto& file : std::filesystem::recursive_directory_iterator(folder))
        file_pathes.emplace_back(file.path().string());

    for (const auto& path : file_pathes)
    {
        sf::Texture texture;
        texture.loadFromFile(path);

        auto start = path.find_last_of("\\");
        auto end = path.find_last_of('.');

        auto texture_name = path.substr(start + 1, end - start - 1);

        m_textures.emplace(std::move(texture_name), texture);
    }
}

sf::Texture* TextureHolder::get(const std::string& name)
{
    if (auto found = m_textures.find(name); found != m_textures.end())
        return &found->second;

    return nullptr;
}