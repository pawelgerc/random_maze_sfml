#include "gameWorld.h"
#include "gameTile.h"
#include <random>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <algorithm>

GameWorld::GameWorld() {
    gridLength = 15;
    poziom = 1;
    algorytm = 1;
    grid.resize(gridLength);
    
    for (int i=0;i<gridLength;i++)
    {
        grid[i].resize(gridLength);
    }
    
    
    setUpInitialState();
}
void GameWorld::setUpInitialState() {
    start = clock();
    exitPos = sf::Vector2i(gridLength-1,gridLength-1);
    playerPos = sf::Vector2i(0, 0);
    it = 0;
    if(algorytm == 0)
    {
        recursivebacktracking();
    }
    else if(algorytm == 1)
    {
        randommaze();
    }
    else if(algorytm == 2)
    {
        kruskal();
    }
}



void GameWorld::kruskal(){
    

	for (int i = 0; i < gridLength; i++)
	{
		for (int j = 0; j < gridLength; j++)
		{
			grid[i][j] = 2;
		}
	}


    int xx = 0;
    int yy = 0;
    
    
    while (canPass(gridLength, gridLength, xx, yy) == false)
    {   
        for (int i = 0; i < gridLength; i++)
        {
            for (int j = 0; j < gridLength; j++)
            {
                grid[i][j] = 2;
            }
        }



        std::vector<Edge> edges;
        for (int y = 0; y < gridLength; y++) {
        for (int x = 0; x < gridLength; x++) {
          if (x > 0) edges.emplace_back(x + y * gridLength, x - 1 + y * gridLength); 
          if (y > 0) edges.emplace_back(x + y * gridLength, x + (y - 1) * gridLength);
        }
        }
        std::random_shuffle(edges.begin(), edges.end()); 

        std::vector<int> parent(gridLength * gridLength);
        for (int i = 0; i < gridLength * gridLength; i++) {
            parent[i] = i; 
        }

        for (const auto e : edges) {
            int rootFrom = findRoot(parent, e.from);
            int rootTo = findRoot(parent, e.to);
            if (rootFrom != rootTo) { 
              parent[rootFrom] = rootTo; 
              int xFrom = e.from % gridLength;
              int yFrom = e.from / gridLength;
              int xTo = e.to % gridLength;
              int yTo = e.to / gridLength;
              if (xFrom == xTo) { 
                grid[xFrom][std::min(yFrom, yTo)] = 0; 
              } else { 
                grid[std::min(xFrom, xTo)][yFrom] = 0; 
              }
            }
        }
        grid[0][0] = 0;
        grid[gridLength - 1][gridLength - 1] = 0;

    }
    grid[0][0] = 4;
    grid[gridLength - 1][gridLength - 1] = 5;
    
    setUpEnemyPositions();
}





int GameWorld::findRoot(std::vector<int>& parent, int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]]; 
        i = parent[i];
    }
    return i;
}




void GameWorld::randommaze(){
    
    srand(time(NULL));

    
	int licznik = 0;
	for (int i = 0; i < gridLength; i++)
	{
		for (int j = 0; j < gridLength; j++)
		{
			grid[i][j] = 2;
		}
	}
    

    int xx = 0, yy = 0;
	grid[0][0] = 0;
	grid[gridLength-1][gridLength-1] = 0;

    while (canPass(gridLength, gridLength, xx, yy) == false)
    {
        for (int i = 0; i < gridLength; i++) {
            for (int j = 0; j < gridLength; j++) {
                grid[i][j] = 2;
            }
        }
        int licznik = 0;
		while (licznik < (gridLength * gridLength / 1.4))
		{
			int randomrow = rand() % gridLength;
			int randomcol = rand() % gridLength;
			if (grid[randomrow][randomcol] == 2)
			{
				grid[randomrow][randomcol] = 0;
				licznik++;
			}

		}
		grid[0][0] = 0;
		grid[gridLength-1][gridLength-1] = 0;

    }
	grid[0][0] = 4;
	grid[gridLength-1][gridLength-1] = 5;
    setUpEnemyPositions();
}


void GameWorld::recursivebacktracking(){


    
    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridLength; j++) {
            grid[i][j] = 1;
        }
    }
  
    generateMaze(0, 0);
    

    
    int xx = 0, yy = 0;
    grid[0][0] = 0;
    grid[gridLength - 1][gridLength - 1] = 0;
    while (canPass(gridLength, gridLength, xx, yy) == false)
    {
        for (int i = 0; i < gridLength; i++) {
            for (int j = 0; j < gridLength; j++) {
                grid[i][j] = 1;
            }
        }

        generateMaze(0, 0);
        

        int xx = 0, yy = 0;
        grid[0][0] = 0;
        grid[gridLength - 1][gridLength - 1] = 0;

    }

    grid[0][0] = 4;
    grid[gridLength - 1][gridLength - 1] = 5;
    
    setUpEnemyPositions();
}

void GameWorld::generateMaze(int x, int y) {

    grid[x][y] = 0;
    std::vector<std::pair<int, int>> directions{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    std::vector<std::pair<int, int>> directions1{ {1, 1}, {-1, 1}, {-1, -1}, {1, -1} };
    std::random_device rd;
    std::mt19937 engine(rd());
    std::shuffle(directions.begin(), directions.end(), engine);
    std::shuffle(directions1.begin(), directions1.end(), engine);

    int wx1 = x + directions1[0].first;
    int wy1 = y + directions1[0].second;
    if (wx1 >= 0 && wx1 < gridLength && wy1 >= 0 && wy1 < gridLength) {
        if (grid[wx1][wy1] == 1) {
            grid[wx1][wy1] = 2;
        }
    }


    for (const auto d : directions) {
        int dx = x + d.first;
        int dy = y + d.second;
        if (dx >= 0 && dx < gridLength && dy >= 0 && dy < gridLength) {
            if (grid[dx][dy] == 1) {
                grid[dx][dy] = 0;
                generateMaze(dx, dy);
            }
        }
    }
}




bool GameWorld::canPass(int rows, int cols, int xx, int yy) {
    if (xx < 0 || xx >= rows || yy < 0 || yy >= cols) {
        return false;
    }
    else if (grid[xx][yy] == 2) {
        return false;
    }
    else if (grid[xx][yy] == 3) {
        return false;
    }
    else if (xx == rows - 1 && yy == cols - 1) {
        return true;
    }
    else {
        grid[xx][yy] = 3; 
        return canPass(rows, cols, xx - 1, yy) ||
            canPass(rows, cols, xx + 1, yy) ||
            canPass(rows, cols, xx, yy - 1) ||
            canPass(rows, cols, xx, yy + 1);
    }
}

void GameWorld::setUpEnemyPositions() {
    enemyPositions.clear();
    

    while(enemyPositions.size() < poziom)
    {
        int randomrow = (rand() % (gridLength - 2)) + 2;
        int randomcol = (rand() % (gridLength - 2)) + 2;
        if(grid[randomrow][randomcol] == 3 and grid[randomrow][randomcol] != 8 )
        {
            grid[randomrow][randomcol] = 8;
            enemyPositions.push_back(sf::Vector2i(randomcol,randomrow));
        }
    }
    
    
    setUpDiamond();
}


void GameWorld::setUpDiamond() {
    diamondPosition.clear();
    
    while(diamondPosition.size() != 1)
    {
        int randomrow = (rand() % gridLength);
        int randomcol = (rand() % gridLength);
        if(grid[randomrow][randomcol] == 3 and grid[randomrow][randomcol] != 8 )
        {
            grid[randomrow][randomcol] = 6;
            diamondPosition.push_back(sf::Vector2i(randomcol,randomrow));
        }
    }
    
    setUpTiles();
}



void GameWorld::setUpTiles() {
    tiles.clear();
    int lacznie = 0;
    
    
for (int i=0; i<gridLength; i++)
{
    std::vector<GameTile *> Row;
	for(int j=0; j<gridLength; j++)
	{

        if(grid[i][j] == 0 or grid[i][j] == 3)
        {
            Row.push_back(new GameTile("ground.png",j*50,(i*50)+150,true,false));
        }
        else if(grid[i][j] == 1 or grid[i][j] == 2)
        {
            Row.push_back(new GameTile("wall.png",j*50,(i*50)+150,false,false));
            lacznie = lacznie + 1;
        }
        else if(grid[i][j] == 4)
        {
            Row.push_back(new GameTile("player.png",j*50,(i*50)+150,true,false));
        }
        else if(grid[i][j] == 8)
        {
            Row.push_back(new GameTile("enemy.png",j*50,(i*50)+150,true,false));
        }
        else if(grid[i][j] == 5)
        {
            Row.push_back(new GameTile("door.png",j*50,(i*50)+150,true,true));
        }
        else if(grid[i][j] == 6)
        {
            Row.push_back(new GameTile("diamond.png",j*50,(i*50)+150,true,false));
        }
        if(j==gridLength-1)
        {
            tiles.push_back(Row);
            Row.clear();
        }

	}

}    
    stop = clock();
    czas = (double)(stop - start) / CLOCKS_PER_SEC;
    std::cout<<"<Mape wygenerowane w czasie: " << czas << std::endl;  
    std::cout << "Ilosc scian : " << lacznie << std::endl;    

}
void GameWorld::moveLeft() {
    if (playerPos.x == 0) 
    {
         return; 
    }
    
    if (!tiles[playerPos.y][playerPos.x-1]->isPassable) 
    { 
        return;
    }
    
    tiles[playerPos.y][playerPos.x]->setUpSprite("ground.png");
    playerPos.x -= 1;

    checkCollisionsAndMoveEnemies();
}


void GameWorld::moveUp() {
    if (playerPos.y == 0) 
    { 
        return; 
    }
    if (!tiles[playerPos.y-1][playerPos.x]->isPassable) 
    { 
        return; 
    }
    
    tiles[playerPos.y][playerPos.x]->setUpSprite("ground.png");
    playerPos.y -= 1;

    checkCollisionsAndMoveEnemies();
}

void GameWorld::moveRight() {
    if (playerPos.x == gridLength-1) 
    { 
        return; 
    }
    if (!tiles[playerPos.y][playerPos.x+1]->isPassable) 
    { 
        return; 
    }
    
    tiles[playerPos.y][playerPos.x]->setUpSprite("ground.png");
    playerPos.x += 1;

    checkCollisionsAndMoveEnemies();
}

void GameWorld::moveDown() {
    if (playerPos.y == gridLength-1) 
    { 
        return; 
    }
    if (!tiles[playerPos.y+1][playerPos.x]->isPassable) 
    { 
        return; 
    }
    
    tiles[playerPos.y][playerPos.x]->setUpSprite("ground.png");
    playerPos.y += 1;

    checkCollisionsAndMoveEnemies();
}

void GameWorld::Skip() {

    checkCollisionsAndMoveEnemies();
}


void GameWorld::redrawSprites() {
    if(it != 1)
    {
        tiles[diamondPosition[0].y][diamondPosition[0].x]->setUpSprite("diamond.png");
    }

    tiles[playerPos.y][playerPos.x]->setUpSprite("player.png");
    for (int i = 0; i < enemyPositions.size(); i++) 
    {
        sf::Vector2i currentEnemyPos = enemyPositions[i];
        tiles[enemyPositions[i].y][enemyPositions[i].x]->setUpSprite("enemy.png");
        
        if(diamondPosition[0] == enemyPositions[i] and it != 1)
        {
            tiles[currentEnemyPos.y][currentEnemyPos.x]->setUpSprite("enemyondiamond.png");
        }
        
    }
    
    
    if(diamondPosition[0] == playerPos)
    {
        tiles[playerPos.y][playerPos.x]->setUpSprite("player.png");
        diamondPosition.clear();
    }

    

}


void GameWorld::moveEnemies() {
    for (int i = 0; i < enemyPositions.size(); i++) {
        sf::Vector2i currentEnemyPos = enemyPositions[i];
        std::vector<sf::Vector2i> freePositions = getFreeCoordinates(currentEnemyPos);
        if(freePositions.size() == 0)
        {
            enemyPositions[i] = currentEnemyPos;
        }
        else
        {
            std::random_device rd;
            std::mt19937 engine(rd());
            std::shuffle(freePositions.begin(),freePositions.end(),engine);
            sf::Vector2i newPos = freePositions[0];
            tiles[currentEnemyPos.y][currentEnemyPos.x]->setUpSprite("ground.png");
            enemyPositions[i] = newPos;
        }
    }
}


std::vector<sf::Vector2i> GameWorld::getFreeCoordinates(sf::Vector2i currentPos) {
    
    std::vector<sf::Vector2i> freePositions;
    std::vector<sf::Vector2i> allPositions;
    
    allPositions.push_back(sf::Vector2i(currentPos.x-1,currentPos.y));
    allPositions.push_back(sf::Vector2i(currentPos.x,currentPos.y-1));
    allPositions.push_back(sf::Vector2i(currentPos.x+1,currentPos.y));
    allPositions.push_back(sf::Vector2i(currentPos.x,currentPos.y+1));


    for (int i = 0; i < 4; i++) {
        if (checkIfPositionIsFree(allPositions[i])) 
        {
            freePositions.push_back(allPositions[i]);
        }
    }

    return freePositions;
}
    
    
bool GameWorld::checkIfPositionIsFree(sf::Vector2i pos) {
    if (pos.x < 0 || pos.y < 0 || pos.x > gridLength - 1 || pos.y > gridLength - 1) {
        return false;
    }
    if (!tiles[pos.y][pos.x]->isPassable) {
        return false;
    }
    if (tiles[pos.y][pos.x]->isExit) {
        return false;
    }
    return true;
}


void GameWorld::checkCollisionsAndMoveEnemies() {
    if (checkIfReachedExit()) 
    {
        poziom++;
        score = score + 10;
        setUpInitialState();
        return;
    }
    if (checkIfReachedDiamond()) 
    {
        if(it == 0)
        {
            it = 1;
            score = score + 5;
        }
    }
    moveEnemies();
    if (checkIfTouchedEnemy()) {
        setUpInitialState();
        return;
    }
    redrawSprites();
}




bool GameWorld::checkIfReachedExit() 
{
    return playerPos.x == exitPos.x && playerPos.y == exitPos.y;
}



bool GameWorld::checkIfReachedDiamond() 
{
    return playerPos.x == diamondPosition[0].x && playerPos.y == diamondPosition[0].y;
}



bool GameWorld::checkIfTouchedEnemy () {
    for (int i = 0; i < enemyPositions.size(); i++) {
        sf::Vector2i currentEnemyPos = enemyPositions[i];
        if (playerPos.x == currentEnemyPos.x && playerPos.y == currentEnemyPos.y) 
        {
            table();
            return true;
        }
    }
    return false;
}

void GameWorld::table(){
    
    tablica.clear();
	std::pair<int, std::string> q;

	std::ifstream plik("score.txt");
	if (plik.is_open()) {
		std::string linia, data;
		int liczba;
		while (getline(plik, linia)) {
			std::stringstream ss(linia);
			ss >> liczba >> data;
			q = { liczba,data };
			tablica.push_back(q);	
		}

		plik.close();
	}
	else {
		std::cout << "Nie można otworzyć pliku" << std::endl;
	}

    std::fstream scoresave;
    scoresave.open("score.txt", std::ios::app);
    if(scoresave.is_open())
    {
        time_t aktualnyczas = time(0);
        tm* czaslokalny = localtime(&aktualnyczas);
        char data[17];
        strftime(data,sizeof(data), "%Y-%m-%d,%H:%M", czaslokalny);
        scoresave << score << " " << data <<std::endl;
        q = { score, data };
        tablica .push_back(q);
        scoresave.close();
    }
	
	sort(tablica.begin(), tablica.end());
	int a = 0;
	for (int i = 0; i < tablica.size(); i++)
	{
		if (tablica[i] == q)
		{
			a = i;
		}
		
	}

    temp = tablica .size() - a;

	std::cout << "Uzyskałeś : " << score << " punktow. Jest to " << temp << " wynik w historii." << std::endl;
    sprawdz = 1;
    
    
}
void GameWorld::framehide(){
    sprawdz = 0;
    score = 0;
	poziom = 1;
    setUpInitialState();
    
}


