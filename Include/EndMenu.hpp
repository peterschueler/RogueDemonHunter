#ifndef ENDMENU_HPP
#define ENDMENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class EndMenu : public sf::NonCopyable {
public:
	explicit EndMenu(sf::RenderWindow&, bool);
	
	void update(sf::Time);
	void draw();
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	sf::Sprite background;
	sf::Texture texture;
};

#endif