#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

enum Fonts
{
    BulkyPixel,
    NeonPixel7,
    Yoster,
    Spaceboy,
    LightPixel

};

class Text
{
private:
    TTF_Font *font;
    std::string prefix = "/fonts/";
    std::string full_path;
    Fonts picked_font;
    int font_size;
    std::string path_to_assets_folder;
    int deRefcount = 0;
    int unsuccesfullRefCount = 0;
    void swap(Text &first, Text &second);

public:
    static int instance_counter;
    static std::unordered_map<Fonts, std::string> available_fonts;
    std::string getFullPath(std::string path_to_assets_folder);
    std::string searchForAssets();
    Text(Fonts fonts, int font_size, std::string path_to_assets_folder);
    Text() : Text(Fonts::BulkyPixel, 30, ""){};
    // not copyable
    Text(Text const &) = delete;
    Text &operator=(Text const &) = delete;
    // moveable -> copy the pointer over, then set it to null in the original (i.e. transfer ownership)
    Text(Text &&txt);
    Text &operator=(Text &&txt);
    ~Text();
    void displayText(int x, int y, std::string text, SDL_Color color, SDL_Renderer *renderer);
};

std::unordered_map<Fonts, std::string> Text::available_fonts({{Fonts::BulkyPixel, "bulkypix.ttf"}, {Fonts::NeonPixel7, "neon_pixel-7.ttf"}, {Fonts::Yoster, "yoster.ttf"}, {Fonts::Spaceboy, "spaceboy.ttf"}, {Fonts::LightPixel, "light_pixel-7.ttf"}});
int Text::instance_counter = 0;

Text::Text(Fonts picked_font, int font_size, std::string path_to_assets_folder) : picked_font(picked_font), font_size(font_size), path_to_assets_folder(path_to_assets_folder)
{
    if (instance_counter == 0)
    {
        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            // success = false;
        }
    }
    instance_counter++;
    std::string full_path = getFullPath(searchForAssets());

    font = TTF_OpenFont(full_path.c_str(), font_size);

    std::cout << "Adres: " << font << std::endl;

    if (!font)
    {
        std::cerr << "Failed to load font! " << TTF_GetError() << std::endl;
    }
}

Text::Text(Text &&txt)
{
    swap(*this, txt);
}

Text &Text::operator=(Text &&txt)
{
    swap(*this, txt);
    return *this;
}

void Text::swap(Text &first, Text &second)
{
    std::swap(first.prefix, second.prefix);
    std::swap(first.picked_font, second.picked_font);
    std::swap(first.font_size, second.font_size);
    std::swap(first.path_to_assets_folder, second.path_to_assets_folder);
    std::swap(first.font, second.font);
}

Text::~Text()
{
    if (font != nullptr)
    {
        deRefcount++;
        instance_counter--;
        std::cout << "Dereferencja nr: " << deRefcount << " for address: " << font << std::endl;
        TTF_CloseFont(font);

        if(instance_counter == 0) {
            TTF_Quit();
        }
    }
    else
    {
        unsuccesfullRefCount++;
        std::cout << "Dereferencja nie udana nr: " << unsuccesfullRefCount << " for address: " << font << std::endl;
    }
}

std::string Text::getFullPath(std::string path_to_assets_folder)
{
    std::filesystem::path p = path_to_assets_folder;
    std::string abs_path = std::filesystem::absolute(p).generic_string();
    return abs_path + prefix + available_fonts[picked_font];
}

std::string Text::searchForAssets()
{
    std::string path = "./";
    std::string search_string = "assets";
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        size_t find = entry.path().generic_string().find(search_string);
        if (find != std::string::npos)
            return entry.path().generic_string();
    }

    path = "../";
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        size_t find = entry.path().generic_string().find(search_string);
        if (find != std::string::npos)
            return entry.path().generic_string();
    }

    return "";
}

void Text::displayText(int x, int y, std::string text, SDL_Color color, SDL_Renderer *renderer)
{
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_Rect Text_Proper_Size_Rect;
    SDL_QueryTexture(text_texture, nullptr, nullptr, &Text_Proper_Size_Rect.w, &Text_Proper_Size_Rect.h);
    Text_Proper_Size_Rect.x = x;
    Text_Proper_Size_Rect.y = y;

    SDL_RenderCopy(renderer, text_texture, NULL, &Text_Proper_Size_Rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}
