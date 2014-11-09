#include <iostream>
#include <vector>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include "graphics/TileMap.h"

struct Card
{
    int priority;
    char type;
};

sf::VideoMode getBestFullscreenMode()
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode bestMode = modes[0];

    for (std::size_t i = 0; i < modes.size(); i++) {
        if (modes[i].width > bestMode.width)
            bestMode = modes[i];
        else if (modes[i].width == bestMode.width) {
            if (modes[i].height > bestMode.height)
                bestMode = modes[i];
        }
    }

    return bestMode;
}

TileMap map;
std::vector<std::vector<int>> level;

void onZoomIn ()
{
    map.zoomIn(level);
}

void onZoomOut ()
{
    map.zoomOut(level);
}

void onNorth () {
    map.move(level, 0,-1);
}

void onWest () {
    map.move(level, -1,0);
}

void onSouth () {
    map.move(level, 0,1);
}

void onEast () {
    map.move(level, 1,0);
}

void onAddCard(Card card, int index) {

}

void makeCard(Card card, int index) {
    auto cardButton = sfg::Button::Create("" + std::to_string(card.priority) + " " + std::to_string(card.type));
    cardButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(onAddCard, card, index));
}

class CardManager
{
    public:
        CardManager();
        void placeCardPos(int index);
        void placeCardCos(int index);
    private:
        Card allCards[9];
        std::vector<Card> posCards;
        std::vector<Card> cosCards;
};

CardManager::CardManager ()
{
    allCards[0].priority = 500;
    allCards[0].type = 1;
    allCards[1].priority = 500;
    allCards[1].type = 1;
    allCards[2].priority = 500;
    allCards[2].type = 1;
    allCards[3].priority = 500;
    allCards[3].type = 1;
    allCards[4].priority = 500;
    allCards[4].type = 1;
    allCards[5].priority = 500;
    allCards[5].type = 1;
    allCards[6].priority = 500;
    allCards[6].type = 1;
    allCards[7].priority = 500;
    allCards[7].type = 1;
    allCards[8].priority = 500;
    allCards[8].type = 1;
}

void CardManager::placeCardPos(int index)
{
    posCards.push_back(allCards[index]);
}

void CardManager::placeCardCos(int index)

int main()
{
    sf::RenderWindow render_window(getBestFullscreenMode(), "RoboRally", sf::Style::Fullscreen);

    sfg::SFGUI m_sfgui;

    auto zoomInButton = sfg::Button::Create("Zoom In");
    auto zoomOutButton = sfg::Button::Create("Zoom Out");

    auto goNorth = sfg::Button::Create("Move North");
    auto goWest = sfg::Button::Create("Move West");
    auto goSouth = sfg::Button::Create("Move South");
    auto goEast = sfg::Button::Create("Move East");

    auto moveBotBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    moveBotBox->Pack(goWest, false);
    moveBotBox->Pack(goSouth, false);
    moveBotBox->Pack(goEast, false);

    auto moveBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    moveBox->Pack(goNorth, false);
    moveBox->Pack(moveBotBox);

    zoomInButton->GetSignal(sfg::Widget::OnLeftClick).Connect(onZoomIn);
    zoomOutButton->GetSignal(sfg::Widget::OnLeftClick).Connect(onZoomOut);

    goNorth->GetSignal(sfg::Widget::OnLeftClick).Connect(onNorth);
    goWest->GetSignal(sfg::Widget::OnLeftClick).Connect(onWest);
    goSouth->GetSignal(sfg::Widget::OnLeftClick).Connect(onSouth);
    goEast->GetSignal(sfg::Widget::OnLeftClick).Connect(onEast);

    auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

    //box->Pack( m_label );
    box->Pack(zoomInButton, false);
    box->Pack(zoomOutButton, false );

    box->Pack(moveBox);

    auto middleBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f); //vertical container for middle

    auto allBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f); //container for everything
    //allBox->pack

    // Create a desktop and add the window to it.
    sfg::Desktop desktop;

    //desktop.Add( window );
    desktop.Add(box);

    render_window.resetGLStates();

    // Main loop!
    sf::Event event;
    sf::Clock clock;

    int tmp [10][10] =
    {
        {0,1,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,1,0,0,1,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {1,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,1,0,0,0,0,0,0,0,0}
    };

    for (int i = 0; i < 10; i++) {
        level.push_back(std::vector<int>());
        for (int j = 0; j < 10; j++) {
            level[i].push_back(tmp[i][j]);
        }
    }

    if (!map.load(80, level, 10, 10))
        return -1;

    map.setPosition(400,0);

    while( render_window.isOpen() ) {
        // Event processing.
        while( render_window.pollEvent( event ) ) {
            desktop.HandleEvent( event );
            // If window is about to be closed, leave program.
            if (event.type == sf::Event::Closed) {
                render_window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                render_window.close();
            }
        }
        // Update SFGUI with elapsed seconds since last call.
        desktop.Update( clock.restart().asSeconds() );
        // Rendering.
        render_window.clear();
        m_sfgui.Display( render_window );
        render_window.draw(map);
        render_window.display();
    }
    return 0;
}
