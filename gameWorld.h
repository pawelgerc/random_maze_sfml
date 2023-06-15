#include <SFML/Graphics.hpp>
#include "gameTile.h"
#include <vector>
#include <ctime>
#include <string>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H


class GameWorld {
    sf::Vector2i exitPos;
    sf::Vector2i playerPos;
    std::vector<sf::Vector2i> enemyPositions;
    std::vector<sf::Vector2i> diamondPosition;
    clock_t start,stop;
    double czas;
    void randommaze();
    void recursivebacktracking();
    void generateMaze(int x, int y);
    bool canPass(int rows, int cols, int xx, int yy);
    int randomIndex;
    int it;
    class Edge {
    public:
        int from, to;

        Edge(int f, int t) : from(f), to(t) {}
    };
    int findRoot(std::vector<int>& parent, int i);
    void kruskal();

    void setUpEnemyPositions();
    void setUpTiles();
    void redrawSprites();
    std::vector<sf::Vector2i> getFreeCoordinates(sf::Vector2i);
    bool checkIfPositionIsFree(sf::Vector2i);
    void moveEnemies();
    bool checkIfReachedExit();
    bool checkIfReachedDiamond(); 
    bool checkIfTouchedEnemy();
    void checkCollisionsAndMoveEnemies();
    void table();
    void setUpDiamond();
public:
    int sprawdz = 0;
    int temp = 0;
    void framehide();
    void setUpInitialState();
    std::vector< std::vector<GameTile *> > tiles;
    std::vector< std::vector<int> > grid;
    std::vector<std::pair<int, std::string>> tablica;
    int gridLength;
    int poziom;
    int score = 0;
    int algorytm;
    GameWorld();
    void moveLeft();
    void moveUp();
    void moveRight();
    void moveDown();
    void Skip();
    
};

#endif
