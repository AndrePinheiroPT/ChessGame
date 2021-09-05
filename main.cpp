#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#define size 54

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

Sprite pieces[8][8];

void printBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}

void loadPieces(){
    int imgSize = 200;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int piece = board[i][j];
            if (!piece) continue;

            int x = abs(piece) -1;
            int y = piece > 0 ? 0 : 1;

            pieces[i][j].setTextureRect( IntRect(imgSize*x, imgSize*y, imgSize, imgSize));
            pieces[i][j].setPosition(size*j, size*i);
        }
    }
}

bool checkPieceCanMove(int pieceSquare[], int toSquare[], bool whiteTurn){
    bool canMove = false;
    switch(abs(board[pieceSquare[1]][pieceSquare[0]])){
        case 1:
            if(pieceSquare[1] - 1 == toSquare[1] || pieceSquare[1] + 1 == toSquare[1] || pieceSquare[0] - 1 == toSquare[0] || pieceSquare[0] + 1 == toSquare[0]) 
            if(board[toSquare[1]][toSquare[0]] == 0 || (board[toSquare[1]][toSquare[0]] < 0 && whiteTurn) || (board[toSquare[1]][toSquare[0]] > 0 && !whiteTurn)) canMove = true;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            if(pieceSquare[1] - 1 == toSquare[1]) cout << "FAY" << endl;
            break;
    default:
        break;
    }
    return canMove;
}

int main(){
    RenderWindow window(sf::VideoMode(432, 432), "Chess Game!");

    Texture figures;
    figures.loadFromFile("img/pieces.png");

    Sprite figuresSprite(figures), noneSprite;
    figuresSprite.setScale(Vector2f(0.27, 0.27));

    bool move = false;
    bool whiteTurn = true;
    bool blackTurn = false;

    int pieceSquare[2];
    Vector2f prevPosition;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(!board[i][j]) continue;
            pieces[i][j] = figuresSprite;
        } 
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
                    for (int i = 0; i < 8; i++){
                        for (int j = 0; j < 8; j++){
                            if (pieces[j][i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                move = true;
                                pieceSquare[0] = i;
                                pieceSquare[1] = j;
                            }
                        }
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased){
                if (event.key.code == Mouse::Left){
                    move = false;
                    for(int i = 0; i < 8; i++){
                        for(int j = 0; j < 8; j++){
                            if (size*i <= mousePosition.x && (1 + i)*size >= mousePosition.x &&
                            size*j <= mousePosition.y && (1 + j)*size >= mousePosition.y){

                                if((board[pieceSquare[1]][pieceSquare[0]] > 0 && whiteTurn) || (board[pieceSquare[1]][pieceSquare[0]] < 0 && blackTurn)){
                                    int square[2] = {j, i};
                                    if(checkPieceCanMove(pieceSquare, square, whiteTurn)){
                                        pieces[j][i] = pieces[pieceSquare[1]][pieceSquare[0]];
                                        pieces[j][i].setPosition(size*i, size*j);

                                        pieces[pieceSquare[1]][pieceSquare[0]] = noneSprite;
                                        
                                        board[j][i] = board[pieceSquare[1]][pieceSquare[0]];
                                        board[pieceSquare[1]][pieceSquare[0]] = 0;

                                        if(blackTurn){
                                            whiteTurn = true;
                                            blackTurn = false;
                                        }else if(whiteTurn){
                                            whiteTurn = false;
                                            blackTurn = true;
                                        }
                                    }else{
                                        pieces[pieceSquare[1]][pieceSquare[0]].setPosition(pieceSquare[0]*size, pieceSquare[1]*size);
                                    }
                                }else{
                                    pieces[pieceSquare[1]][pieceSquare[0]].setPosition(pieceSquare[0]*size, pieceSquare[1]*size);
                                }
                                printBoard();
                            }
                        }
                    }
                }
            }
        }
        
        if (move){
            pieces[pieceSquare[1]][pieceSquare[0]].setPosition(mousePosition.x-27, mousePosition.y-27);
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

        for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) window.draw(pieces[i][j]);

        window.display();
    }

    return 0;
}
