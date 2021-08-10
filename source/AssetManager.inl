#include <filesystem>

template<class Resource>
void AssetManager<Resource>::load(const std::string_view folder)
{
    std::list<std::filesystem::path> file_pathes;

    for (auto& file : std::filesystem::recursive_directory_iterator(folder))
        file_pathes.emplace_back(file.path());

    for (const auto& path : file_pathes)
    {
        Resource resource;

        if (resource.loadFromFile(path.string()))
            m_resources.emplace(path.stem().string(), resource);       
    }
}

template<class Resource>
Resource* AssetManager<Resource>::get(const std::string& name)
{
    if (auto found = m_resources.find(name); found != m_resources.end())
        return &found->second;

    return nullptr;
}
