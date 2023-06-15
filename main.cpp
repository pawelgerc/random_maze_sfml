#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "gameWorld.cpp"
#include "gameTile.cpp"
#include "gameWorld.h"
#include "gameTile.h"
#include <iostream>


int main()
{	
    float windowHeight = 900;
    float windowWidth = 750;
    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Rougelike");
    GameWorld gameWorld = GameWorld();
    

    
    sf::Sprite butt1, butt2,butt3, background, frame;
    sf::Texture button1, button2,button3, background1, frame1;
    if(!frame1.loadFromFile("frame.png"))
    {
	return 1;
    }
    if(!background1.loadFromFile("option.png"))
    {
	return 1;
    }
    if(!button1.loadFromFile("yes.png"))
    {
	return 1;
    }
    if(!button2.loadFromFile("no.png"))
    {
	return 1;
    }
    if(!button3.loadFromFile("no.png"))
    {
	return 1;
    }
    
    frame.setTexture(frame1);
    frame.setPosition(window.getSize().x * 0.2,window.getSize().y * 0.33);
    
    background.setTexture(background1);
    background.setPosition(0,0);
    butt1.setTexture(button1);
    butt1.setPosition(window.getSize().x / 1.5,window.getSize().y * 0.035);
    butt2.setTexture(button2);
    butt2.setPosition(window.getSize().x / 1.5,window.getSize().y * 0.07);
    butt3.setTexture(button3);
    butt3.setPosition(window.getSize().x / 1.5,window.getSize().y * 0.105);
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
    {
        return 1;
    }
    sf::Text point, lvl, alg1, alg2,alg3, wynik, ent;
    
    alg1.setFont(font);
    alg1.setCharacterSize(18);
    alg1.setPosition(window.getSize().x / 1.4,window.getSize().y * 0.035);
    alg1.setString("Recursive");
    alg1.setStyle(sf::Text::Bold);
    alg1.setFillColor(sf::Color::Black);    
    
    alg2.setFont(font);
    alg2.setCharacterSize(18);
    alg2.setPosition(window.getSize().x / 1.4,window.getSize().y * 0.07);
    alg2.setString("Random");
    alg2.setStyle(sf::Text::Bold);
    alg2.setFillColor(sf::Color::Black);    
    
    alg3.setFont(font);
    alg3.setCharacterSize(18);
    alg3.setPosition(window.getSize().x / 1.4,window.getSize().y * 0.105);
    alg3.setString("Kruskal");
    alg3.setStyle(sf::Text::Bold);
    alg3.setFillColor(sf::Color::Black); 
    
    
    point.setFont(font);
    point.setCharacterSize(24);
    point.setFillColor(sf::Color::Black);  
    point.setStyle(sf::Text::Bold); 
    point.setPosition(window.getSize().x *0.13,window.getSize().y * 0.0389);
    
    lvl.setFont(font);
    lvl.setCharacterSize(24);
    lvl.setFillColor(sf::Color::Black);  
    lvl.setStyle(sf::Text::Bold); 
    lvl.setPosition(window.getSize().x *0.13,window.getSize().y * 0.0888);

    while (window.isOpen())
    {
	std::string pkt = std::to_string(gameWorld.score);
	std::string lv = std::to_string(gameWorld.poziom);
	point.setString("Punkty : " + pkt);
	lvl.setString("Poziom : " + lv);
        sf::Event event;
	

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
	    {
                window.close();
		exit(0);
	    }
        
	    else if (event.type == sf::Event::KeyPressed) 
	    {
		
		if(gameWorld.sprawdz == 0)
		{
		    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		    {
			gameWorld.moveLeft();
		    } 
		    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		    {
			gameWorld.moveUp();
		    } 
		    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		    {
			gameWorld.moveRight();
		    } 
		    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		    {
			gameWorld.moveDown();
		    }
		    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
		    {
			gameWorld.Skip();
		    }
		
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
		{
		    gameWorld.framehide();
		}
	    }
	    else if (event.type == sf::Event::MouseButtonPressed)
	    {
		switch(event.key.code)
		{
		    case sf::Mouse::Left:
		    {
			if(sf::Mouse::getPosition(window).x > 0.67 * window.getSize().x && sf::Mouse::getPosition(window).x < 0.7 * window.getSize().x && sf::Mouse::getPosition(window).y > 0.035 * window.getSize().y && sf::Mouse::getPosition(window).y < 0.062 * window.getSize().y)
			{
			    if(!button1.loadFromFile("yes.png"))
			    {
				return 1;
			    }
			    if(!button2.loadFromFile("no.png"))
			    {
				return 1;
			    }
			    if(!button3.loadFromFile("no.png"))
			    {
				return 1;
			    }
			    gameWorld.score = 0;
			    gameWorld.algorytm = 0;
			    gameWorld.poziom = 1;
			    gameWorld.setUpInitialState();
			}
			else if (sf::Mouse::getPosition(window).x > 0.67 * window.getSize().x && sf::Mouse::getPosition(window).x < 0.7 * window.getSize().x && sf::Mouse::getPosition(window).y > 0.072 * window.getSize().y && sf::Mouse::getPosition(window).y < 0.099 * window.getSize().y)
			{
			    if(!button1.loadFromFile("no.png"))
			    {
				return 1;
			    }
			    if(!button2.loadFromFile("yes.png"))
			    {
				return 1;
			    }
			    if(!button3.loadFromFile("no.png"))
			    {
				return 1;
			    }			    
			    gameWorld.score = 0;
			    gameWorld.algorytm = 1;
			    gameWorld.poziom = 1;
			    gameWorld.setUpInitialState();
			}
			else if (sf::Mouse::getPosition(window).x > 0.67 * window.getSize().x && sf::Mouse::getPosition(window).x < 0.7 * window.getSize().x && sf::Mouse::getPosition(window).y > 0.107 * window.getSize().y && sf::Mouse::getPosition(window).y < 0.134 * window.getSize().y)
			{
			    if(!button1.loadFromFile("no.png"))
			    {
				return 1;
			    }
			    if(!button2.loadFromFile("no.png"))
			    {
				return 1;
			    }
			    if(!button3.loadFromFile("yes.png"))
			    {
				return 1;
			    }			    
			    gameWorld.score = 0;
			    gameWorld.poziom = 1;
			    gameWorld.algorytm = 2;
			    gameWorld.setUpInitialState();
			}			
		    }
		}
	    }
	}
    window.clear(sf::Color{255,213,128});
    window.draw(background); 
    window.draw(alg1);
    window.draw(alg2);
    window.draw(alg3);
    window.draw(point);
    window.draw(lvl);
    window.draw(butt1);
    window.draw(butt2);
    window.draw(butt3);
       
    for(int i=0; i<gameWorld.gridLength; i++)
    {
	for(int j=0; j<gameWorld.gridLength; j++)
	{
	    window.draw(gameWorld.tiles[i][j]->sprite);
	}
    }
    
    if(gameWorld.sprawdz == 1)
    {
	wynik.setFont(font);
	wynik.setCharacterSize(16);
	wynik.setFillColor(sf::Color::Black);  
	wynik.setStyle(sf::Text::Bold); 
	wynik.setPosition(window.getSize().x * 0.4 ,window.getSize().y * 0.455);
	std::string w = "Uzyskane punkty : " + std::to_string(gameWorld.score) + ". \nJest to " + std::to_string(gameWorld.temp) + " wynik w historii.";
	wynik.setString(w);
	
	ent.setFont(font);
	ent.setCharacterSize(16);
	ent.setFillColor(sf::Color::Black);  
	ent.setStyle(sf::Text::Bold); 
	ent.setPosition(window.getSize().x * 0.45 ,window.getSize().y * 0.495);
	ent.setString(L"Wciśnij ENTER");
	
	window.draw(frame);
	window.draw(wynik);
	window.draw(ent);
    }
    
    window.display();
    }

    return 0;

}
