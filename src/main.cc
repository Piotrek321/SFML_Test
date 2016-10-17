#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void setAndLoadSpriteTexture(sf::Texture &texture, sf::Sprite &sprite,sf::Vector2u &PicSize);
void setAndLoadBackground(sf::Texture &texture, sf::Sprite &sprite);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600,32), "Wario!");
    sf::Vector2u PicSize;
 
    sf::Texture Mario ;
    sf::Sprite MarioPic;

    sf::SoundBuffer Jumpbuff;
    sf::Music MainTheme;

    if(!Jumpbuff.loadFromFile("MarioJump.wav")) {
		exit(-21);					//TODO add some console output / more info
    }
    if(!MainTheme.openFromFile("MarioMain.ogg")) {
		exit(-22);					//TODO add some console output / more info
    }
								
    sf::Sound Jump;				
    Jump.setBuffer(Jumpbuff);

    sf::Texture Desert ;
    sf::Sprite DesertPic;
    
    setAndLoadBackground(Desert,DesertPic);
    setAndLoadSpriteTexture(Mario,MarioPic,PicSize);
    
    bool speedFlag = false;
    bool WarioJump = false;
    double WarioSpeed = 1.;


    MainTheme.setLoop(true);
    MainTheme.play(); // New Thread is started here


    while (window.isOpen()) {

	if(WarioJump == true) {
		int j  = 998;
		for(int i = 0 ; i < 20000000 ; i++)
			j = j*i - (i*i-12);		
		MarioPic.move(0,40);
		WarioSpeed = 1;
		WarioJump = false;
	        window.draw(DesertPic);
	        window.draw(MarioPic);
	        window.display();
		for(int i = 0 ; i < 20000000 ; i++)
			j = j*i - (i*i-12);	
		continue; 		 
	} 
	sf::Event event;
        while (window.pollEvent(event)) {

	    if(event.type == sf::Event::Closed)
		window.close();
	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		window.close();

	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {		
		sf::Vector2f position = MarioPic.getPosition();
		
		if(speedFlag == false) {
			WarioSpeed += 0.1;
		}
		else {
			WarioSpeed = 1.;
		}
			
		if((position.x + PicSize.x) <= 800) {
			sf::Vector2f scale = MarioPic.getScale();
			if(scale.x < 0) {
				MarioPic.setScale(1.f,1.f);
				MarioPic.move(-128,0);				//TODO why not -PicSize.x ???		
			}
			else {
				MarioPic.move(WarioSpeed * 20,0);	//TODO sometimes Wario wants to escape from scene
			}
			speedFlag = false;			
		}
	    }

	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
		sf::Vector2f position = MarioPic.getPosition();		
		if(speedFlag == true) {
			WarioSpeed += 0.1;
		}
		else {
			WarioSpeed = 1.;
		}				
		if((position.x + PicSize.x) >= 2*PicSize.x) {
			sf::Vector2f scale = MarioPic.getScale();
			if(scale.x > 0) {
				MarioPic.setScale(-1.f,1.f);
				MarioPic.move(PicSize.x,0);			
			}
			else {			
				MarioPic.move(WarioSpeed * (-20),0);	//TODO sometimes Wario wants to escape from scene
			}
			speedFlag = true;
		}
	
	    }
	    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
		sf::Vector2f position = MarioPic.getPosition();
			if(600-position.y == PicSize.y) {
				Jump.play();
				MarioPic.move(0,-40);
				WarioJump = true;
			}
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

