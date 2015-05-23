#include "asset_manager.hpp"

#include "resource_path.hpp"

Asset_Manager::Asset_Manager()
{

}

Asset_Manager::~Asset_Manager()
{

}

void Asset_Manager::load()
{
    //textures
    load_texture("block_1",     "asset//texture//block_1.png");
    load_texture("block_2",     "asset//texture//block_2.png");
    load_texture("block_3",     "asset//texture//block_3.png");
    load_texture("block_4",     "asset//texture//block_4.png");
    load_texture("block_5",     "asset//texture//block_5.png");
    load_texture("block_6",     "asset//texture//block_6.png");
    load_texture("block_7",     "asset//texture//block_7.png");
    load_texture("block_8",     "asset//texture//block_8.png");
    load_texture("block_9",     "asset//texture//block_9.png");
    load_texture("block_10",    "asset//texture//block_10.png");
    load_texture("block_11",    "asset//texture//block_11.png");
    load_texture("block_12",    "asset//texture//block_12.png");
    load_texture("block_13",    "asset//texture//block_13.png");
    load_texture("block_14",    "asset//texture//block_14.png");
    load_texture("block_17",    "asset//texture//block_17.png");
    load_texture("block_18",    "asset//texture//block_18.png");

    load_texture("button",      "asset//texture//button.png");
    load_texture("back",        "asset//texture//back.png");
    load_texture("ground",      "asset//texture//ground.png");
    load_texture("explosion",   "asset//texture//explosion.png");

    //fonts
    load_font("slash", "asset//font//slash.ttf");

    //sound

}

sf::Texture& Asset_Manager::get_texture(std::string id) const
{
    auto item = m_all_textures.find(id);
    return *item->second;
}

sf::Font& Asset_Manager::get_font(std::string id) const
{
    auto item = m_all_fonts.find(id);
    return *item->second;
}

void Asset_Manager::load_texture(std::string id, std::string path)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    texture->loadFromFile(resourcePath() + path);
    m_all_textures.insert(std::make_pair(id, std::move(texture)));
}

void Asset_Manager::load_font(std::string id, std::string path)
{
    std::unique_ptr<sf::Font> font(new sf::Font);
    font->loadFromFile(resourcePath() + path);
    m_all_fonts.insert(std::make_pair(id, std::move(font)));
}
