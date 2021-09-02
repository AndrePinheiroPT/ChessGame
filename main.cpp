#include <SFML/Graphics.hpp>

using namespace sf;

#define size 54
Sprite pieces[32];

int board[8][8] = {
    {-5, -4, -3, -2, -1, -3, -4, -5},
    {-6, -6, -6, -6, -6, -6, -6, -6},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 6,  6,  6,  6,  6,  6,  6,  6},
    { 5,  4,  3,  2,  1,  3,  4,  5},
};

void loadPieces(){
    int k = 0;
    int imgSize = 200;
    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            int piece = board[i][j];
            if (!piece) continue;

            int x = abs(piece) -1;
            int y = piece > 0 ? 0 : 1;

            pieces[k].setTextureRect( IntRect(imgSize*x, imgSize*y, imgSize, imgSize));
            pieces[k].setPosition(size*j, size*i);
            k++;
        }
    }
}

int main(){
    RenderWindow window(sf::VideoMode(432, 432), "Chess Game!");

    Texture figures;
    figures.loadFromFile("img/pieces.png");

    bool whiteTurn = false;
    float dx=0, dy=0;
    int pieceIndex = 0;

    for (int i = 0; i < 32; i++) {
        pieces[i].setTexture(figures);
        pieces[i].setScale(Vector2f(0.27, 0.27));
    }

    loadPieces();
    
    while (window.isOpen()){
        Event event;
        Vector2i mousePosition = Mouse::getPosition(window);

        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == Event::MouseButtonPressed){
                if (event.key.code == Mouse::Left){
                    for (int k = 0; k < 32; k++){
                        if (pieces[k].getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                            whiteTurn = true;
                            pieceIndex = k;
                            dx = mousePosition.x - pieces[k].getPosition().x;
                            dy = mousePosition.y - pieces[k].getPosition().y;
                        }
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased){
                if (event.key.code == Mouse::Left){
                    whiteTurn = false;
                }
            }
        }
        
        if (whiteTurn){
            pieces[pieceIndex].setPosition(mousePosition.x-dx, mousePosition.y-dy);
        }

        window.clear();

        for(int row = 1; row <= 8; row++){
            for(int collum = 1; collum <= 8; collum++){
                Color lightsq(238, 238, 210); 
                Color blacksq(118, 150, 86); 
                
                Color isLightSquare = (row + collum) % 2 == 0 ? lightsq : blacksq;

                RectangleShape square(Vector2f(size, size));
                square.setFillColor(isLightSquare);
                square.setPosition(Vector2f((row-1)*size, (collum-1)*size));
                window.draw(square);
            }
        }

        for (int i = 0; i < 32; i++) window.draw(pieces[i]);

        window.display();
    }

    return 0;
}
