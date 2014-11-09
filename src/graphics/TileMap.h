#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        bool load (unsigned int tileSize, std::vector<std::vector<int>>, unsigned int width, unsigned int height);
        void zoomIn (std::vector<std::vector<int>> tiles);
        void zoomOut (std::vector<std::vector<int>> tiles);
        void move (std::vector<std::vector<int>> tiles, int xChange, int yChange);
        void reload (std::vector<std::vector<int>> tiles);
    private:
        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        unsigned int curWidth;
        unsigned int width;
        unsigned int height;
        unsigned int curHeight;
        unsigned int tileSize;
        unsigned int curTileSize;
        unsigned int xOffset;
        unsigned int yOffset;
};

#endif
