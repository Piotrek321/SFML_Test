#include <SFML/Graphics.hpp>


void setAndLoadSpriteTexture(sf::Texture &texture, sf::Sprite &sprite,sf::Vector2u &PicSize);
void setAndLoadBackground(sf::Texture &texture, sf::Sprite &sprite);


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600,32), "Wario!");
    sf::Vector2u PicSize;
    sf::Texture Mario ;
    sf::Sprite MarioPic;
    
    sf::Texture Desert ;
    sf::Sprite DesertPic;
    
    setAndLoadBackground(Desert,DesertPic);
    setAndLoadSpriteTexture(Mario,MarioPic,PicSize);


    while (window.isOpen()) {

	sf::Event event;
        while (window.pollEvent(event)) {

	    if(event.type == sf::Event::Closed)
		window.close();
	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		window.close();

	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
		sf::Vector2f position = MarioPic.getPosition();
		if((position.x + PicSize.x) <= 800)
			MarioPic.move(20,0);
	    }

	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
		sf::Vector2f position = MarioPic.getPosition();		
		if((position.x + PicSize.x) >= PicSize.x)
			MarioPic.move(-20,0);
	    }		

        }

        window.draw(DesertPic);
        window.draw(MarioPic);
        window.display();
    }

    return 0;
}

void setAndLoadSpriteTexture(sf::Texture &texture, sf::Sprite &sprite,sf::Vector2u &PicSize) {
    texture.loadFromFile("test.png") ;
    sprite.setTexture(texture);
    PicSize = texture.getSize();
    sprite.setPosition(0,600-PicSize.y);
}

void setAndLoadBackground(sf::Texture &texture, sf::Sprite &sprite) {
    texture.loadFromFile("desert.jpeg") ;
    sprite.setTexture(texture);
}

