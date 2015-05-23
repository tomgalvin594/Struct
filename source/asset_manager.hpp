#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

//this class loads and maintains various assets
class Asset_Manager
{
public:
                            Asset_Manager();
                            ~Asset_Manager();

    //load all the assets
    void                    load();

    sf::Texture             &get_texture(std::string id) const;
    sf::Font                &get_font(std::string id) const;

private:
    void                    load_texture(std::string id, std::string path);
    void                    load_font(std::string id, std::string path);

    std::map<std::string, std::unique_ptr<sf::Texture>> m_all_textures;
    std::map<std::string, std::unique_ptr<sf::Font>>    m_all_fonts;
};

#endif // ASSET_MANAGER_HPP
