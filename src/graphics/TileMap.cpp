#include "TileMap.h"

bool TileMap::load (unsigned int tileSize, std::vector<std::vector<int>> tiles, unsigned int width, unsigned int height)
{
    xOffset = 0;
    yOffset = 0;

    curWidth = width;
    this->width = width;
    curHeight = height;
    this->height = height;
    this->tileSize = tileSize;
    curTileSize = tileSize;

    if (!m_tileset.loadFromFile("tiles/together.png"))
        return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width*height*4);

    int yloc;

    for (unsigned int i = xOffset; i < width+xOffset; ++i) {
        for (unsigned int j = yOffset; j < height+yOffset; ++j) {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
            quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
            quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
            quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

            yloc = 128 * tiles[i][j];

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(0, yloc);
            quad[1].texCoords = sf::Vector2f(128, yloc);
            quad[2].texCoords = sf::Vector2f(128, yloc+128);
            quad[3].texCoords = sf::Vector2f(0, yloc+128);
        }
    }
    return true;
}

void TileMap::reload (std::vector<std::vector<int>> tiles)
{
    m_vertices.resize(curWidth*curHeight*4);

    curTileSize = (int) (tileSize * ((double)width/(double)curWidth));

    int yloc;

    for (unsigned int i = 0; i < curWidth; ++i) {
        for (unsigned int j = 0; j < curHeight; ++j) {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * curWidth) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * curTileSize, j * curTileSize);
            quad[1].position = sf::Vector2f((i + 1) * curTileSize, j * curTileSize);
            quad[2].position = sf::Vector2f((i + 1) * curTileSize, (j + 1) * curTileSize);
            quad[3].position = sf::Vector2f(i * curTileSize, (j + 1) * curTileSize);

            yloc = 128 * tiles[i+xOffset][j+yOffset];

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(0, yloc);
            quad[1].texCoords = sf::Vector2f(128, yloc);
            quad[2].texCoords = sf::Vector2f(128, yloc+128);
            quad[3].texCoords = sf::Vector2f(0, yloc+128);
        }
    }
}

void TileMap::zoomIn (std::vector<std::vector<int>> tiles)
{
    if (curWidth <= 2 or curHeight <= 2)
        return;
    curWidth-=2;
    curHeight-=2;
    yOffset++;
    xOffset++;
    reload(tiles);
}

void TileMap::zoomOut (std::vector<std::vector<int>> tiles)
{
    curWidth+=2;
    if (curWidth > width) {
        curWidth = width;
    } else {
        curHeight+=2;
    }

    if (xOffset != 0)
        xOffset--;
    if (yOffset != 0)
        yOffset--;

    reload(tiles);
}

void TileMap::move (std::vector<std::vector<int>> tiles, int xChange, int yChange)
{
    if (xChange < 0) {
        if (xOffset != 0)
            xOffset+=xChange;
    }
    if (yChange < 0) {
        if (yOffset != 0)
            yOffset+=yChange;
    }

    if (xChange > 0) {
        if (xOffset != width-curWidth)
            xOffset+=xChange;
    }
    if (yChange > 0) {
        if (yOffset != height-curHeight)
            yOffset+=yChange;
    }
    reload(tiles);
}

void TileMap::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}



