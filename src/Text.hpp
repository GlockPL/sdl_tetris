#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

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
    // std::shared_ptr<TTF_Font> font;
    TTF_Font* font;
    std::string prefix = "/../assets/fonts/";
    std::string full_path;
    Fonts picked_font;
    int font_size;
    std::string path_to_assets_folder;
public:
    static std::unordered_map<Fonts, std::string> available_fonts;
    std::string getFullPath(std::string path_to_assets_folder);
    Text(Fonts fonts, int font_size, std::string path_to_assets_folder);
    Text() : Text(Fonts::BulkyPixel, 30, "") {};
    // not copyable
    Text(Text const&) = delete;
    Text& operator=(Text const&) = delete;
    // moveable -> copy the pointer over, then set it to null in the original (i.e. transfer ownership)
    Text(Text&& txt);
    Text& operator=(Text&& txt);
    ~Text();
    void displayText(int x, int y, std::string text, SDL_Color color, SDL_Renderer *renderer);
};


std::unordered_map<Fonts, std::string> Text::available_fonts({{Fonts::BulkyPixel, "bulkypix.ttf"}, {Fonts::NeonPixel7, "neon_pixel-7.ttf"}, {Fonts::Yoster, "yoster.ttf"}, {Fonts::Spaceboy, "spaceboy.ttf"}, {Fonts::LightPixel, "light_pixel-7.ttf"}});

Text::Text(Fonts picked_font, int font_size, std::string path_to_assets_folder): picked_font(picked_font), font_size(font_size), path_to_assets_folder(path_to_assets_folder)
{
    std::string full_path = getFullPath(path_to_assets_folder);

    // font = std::shared_ptr<TTF_Font>(TTF_OpenFont(full_path.c_str(), font_size));
    font = TTF_OpenFont(full_path.c_str(), font_size);

    if(!font) {
        std::cerr << "Failed to load font! " << TTF_GetError() << std::endl;
    }

}

Text::Text(Text&& txt){
    prefix = txt.prefix;
    picked_font = txt.picked_font;
    font_size = txt.font_size;
    path_to_assets_folder = txt.path_to_assets_folder;
    font = txt.font;
    txt.font = nullptr;
}

Text& Text::operator=(Text&& txt) {
    prefix = txt.prefix;
    picked_font = txt.picked_font;
    font_size = txt.font_size;
    path_to_assets_folder = txt.path_to_assets_folder;
    font = txt.font;
    txt.font = nullptr;

    return *this;
}

Text::~Text()
{   
    if(font != nullptr) {
        TTF_CloseFont(font);
    }
    
}

std::string Text::getFullPath(std::string path_to_assets_folder) {
    return path_to_assets_folder + prefix + available_fonts[picked_font];
}

void Text::displayText(int x, int y, std::string text, SDL_Color color, SDL_Renderer *renderer) {
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_Rect Text_Proper_Size_Rect;  
    SDL_QueryTexture(text_texture, nullptr, nullptr, &Text_Proper_Size_Rect.w, &Text_Proper_Size_Rect.h);
    Text_Proper_Size_Rect.x = x;
    Text_Proper_Size_Rect.y = y;

    SDL_RenderCopy(renderer, text_texture, NULL, &Text_Proper_Size_Rect);

    SDL_FreeSurface(text_surface);
}
