#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
class Game
{
private:

	struct Logo //struct, описывающий игровую фишку
	{
		enum LogoType
		{
			BARCA,
			JUVE,
			PSG,
			BANNED,
			EMPTY

		};
		sf::Sprite _logoSprite;
		sf::Texture _logosImage;
		LogoType _logoType;
		Logo();
		void changeLogoType(LogoType logoType, size_t rowsPos, size_t colsPos);
	
		
	};
	sf::RenderWindow _window;
	sf::Event _event;

	std::vector<std::vector<Logo>> _gameObjects;
	Logo _gameObject;

	sf::Sprite _background;
	sf::Texture _backgroundImage;
	sf::Sprite _hint;
	sf::Texture _hintImage;

	sf::CircleShape _currentObject;
	sf::Vector2i _currentIndex;

	bool isCaptured;
	bool isEnd;
	bool isHint;
	bool endSwitcher;

	std::vector<sf::SoundBuffer> _soundBuff;
	std::vector<sf::Sound>_sounds;
	sf::Music _soundtrack;

	sf::Clock _clock;

	sf::Font _font;
	sf::Text _endTextFirstStr;
	sf::Text _endTextSecondStr;

	void initSounds();
	void initImages();
	void initText();

	void pollEvents();
	void generateGameObjects();
	void swap(Logo& current, Logo& next);
	void updateCurrentCoords(sf::Keyboard::Key keyCode);

	void drawGameObjects();
	void switchEndGame();


public:

	Game();

	const bool isRunning() const;
	void update();
	void render();
	void checkEndGame();
	void musicPlay();

};

