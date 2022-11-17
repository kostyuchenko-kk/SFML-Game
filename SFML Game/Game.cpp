#include "Game.h"

void Game::pollEvents()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
        {
            _window.close();
        }

        if (_event.type == sf::Event::KeyPressed)
        {

            if (_event.key.code == sf::Keyboard::Escape)
            {
               _window.close();
            }

            if (!isEnd)
            {
                switch (_event.key.code)
                {
                case sf::Keyboard::Right:

                    if (isCaptured)
                    {
                        if (_currentIndex.x != _gameObjects.size() - 1 //Если след. эл-т пустой и текущий не крайний
                            && _gameObjects[_currentIndex.x + 1][_currentIndex.y]._logoType == Logo::EMPTY)
                        {
                            _sounds[0].play();
                            swap(_gameObjects[_currentIndex.x][_currentIndex.y], _gameObjects[_currentIndex.x + 1][_currentIndex.y]);
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    else
                    {
                        if (_currentIndex.x != _gameObjects.size() - 1)
                        {
                            _sounds[0].play();
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    break;

                case sf::Keyboard::Left:
                    if (isCaptured)
                    {
                        if (_currentIndex.x != 0 //Если пред. эл-т пустой и текущий не крайний...и т.д.
                            && _gameObjects[_currentIndex.x - 1][_currentIndex.y]._logoType == Logo::EMPTY)
                        {
                            _sounds[0].play();
                            swap(_gameObjects[_currentIndex.x][_currentIndex.y], _gameObjects[_currentIndex.x - 1][_currentIndex.y]);
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    else
                    {
                        if (_currentIndex.x != 0)
                        {
                            _sounds[0].play();
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    break;

                case sf::Keyboard::Down:
                    if (isCaptured)
                    {
                        if (_currentIndex.y != _gameObjects[0].size() - 1
                            && _gameObjects[_currentIndex.x][_currentIndex.y + 1]._logoType == Logo::EMPTY)
                        {
                            _sounds[0].play();
                            swap(_gameObjects[_currentIndex.x][_currentIndex.y], _gameObjects[_currentIndex.x][_currentIndex.y + 1]);
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    else
                    {
                        if (_currentIndex.y != _gameObjects[0].size() - 1)
                        {
                            _sounds[0].play();
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    break;
                case sf::Keyboard::Up:

                    if (isCaptured)
                    {
                        if (_currentIndex.y != 0
                            && _gameObjects[_currentIndex.x][_currentIndex.y - 1]._logoType == Logo::EMPTY)
                        {
                            _sounds[0].play();
                            swap(_gameObjects[_currentIndex.x][_currentIndex.y], _gameObjects[_currentIndex.x][_currentIndex.y - 1]);
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    else
                    {
                        if (_currentIndex.y != 0)
                        {
                            _sounds[0].play();
                            updateCurrentCoords(_event.key.code);
                        }
                    }
                    break;

                case sf::Keyboard::Enter:

                    if ((_gameObjects[_currentIndex.x][_currentIndex.y]._logoType == Logo::EMPTY
                        || _gameObjects[_currentIndex.x][_currentIndex.y]._logoType == Logo::BANNED)
                        && !isCaptured)
                    {
                        _sounds[1].play();
                    }
                    else
                    {
                        if (isCaptured)
                        {
                            _sounds[3].play();
                        }
                        else
                        {
                            _sounds[2].play();
                        }

                        isCaptured = !isCaptured;
                    }
                    break;

                case sf::Keyboard::Tab:
                {
                    isHint = !isHint;
                }
                break;

                default:
                    break;
                }

            }
        }
    }
    
}

void Game::generateGameObjects()
{
    
    std::vector<Logo::LogoType> generation_tmp;
    generation_tmp.resize(15);
    for (size_t i = 0; i < generation_tmp.size()/3; ++i)
    {
        generation_tmp[i] = Logo::BARCA;
        generation_tmp[i + 5] = Logo::JUVE;
        generation_tmp[i + 10] = Logo::PSG;

    }

    std::shuffle(generation_tmp.begin(), generation_tmp.end(), std::random_device());

    _gameObjects.resize(5);
    for (size_t i = 0; i < _gameObjects.size(); ++i) //заполнение вектора игровых фишек согласно структуре игры
    {
        _gameObjects[i].resize(5);

            for (size_t j = 0; j < _gameObjects[i].size(); ++j)
            {
                if (i % 2 == 0)
                {
                    _gameObject.changeLogoType(generation_tmp[j + i * 5 / 2], j, i);
                    _gameObjects[i][j] = _gameObject;
                   
                }
                else
                {
                    if (j % 2 == 0)
                    {
                        _gameObject.changeLogoType(Logo::BANNED, j, i);
                        _gameObjects[i][j] = _gameObject;
                       
                    }
                    else
                    {
                        _gameObject.changeLogoType(Logo::EMPTY, j, i);
                        _gameObjects[i][j] = _gameObject;
                        
                    }
                
                }
               
            }
    }


}

void Game::drawGameObjects()
{
    if (!isEnd)
    {
        _window.draw(_background);
        for (const auto& cols : _gameObjects)
        {
            for (const auto& el : cols)
            {
                _window.draw(el._logoSprite);
            }
        }
        _window.draw(_currentObject);

        if (isHint)
        {
            _window.draw(_hint);
        }

    }
    else
    {
        _window.draw(_background);
        _window.draw(_endTextFirstStr);
        _window.draw(_endTextSecondStr);
    }

}

void Game::swap(Logo& current, Logo& next)
{
    Logo tmp = current;
    tmp._logoSprite.setPosition(next._logoSprite.getPosition());
    next._logoSprite.setPosition(current._logoSprite.getPosition());
    current = next;
    next = tmp;

}

void Game::updateCurrentCoords(sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {
    case sf::Keyboard::Right:
        ++_currentIndex.x;
        _currentObject.setPosition(280.f + 100.f * _currentIndex.x, _currentObject.getPosition().y);
        break;

    case sf::Keyboard::Left:
        --_currentIndex.x;
        _currentObject.setPosition(280.f + 100.f * _currentIndex.x, _currentObject.getPosition().y);
        break;

    case sf::Keyboard::Down:
        ++_currentIndex.y;
        _currentObject.setPosition(_currentObject.getPosition().x, 103.f + 100.f * _currentIndex.y);
        break;

    case sf::Keyboard::Up:
        --_currentIndex.y;
        _currentObject.setPosition(_currentObject.getPosition().x, 103.f + 100.f * _currentIndex.y);
        break;

    default:
        break;
    }
}



Game::Game()
    :_window{ sf::VideoMode(1060, 706), "The game", sf::Style::Titlebar | sf::Style::Close },
    _currentObject{ 50.f },
    _currentIndex{ 0,0 },
    isCaptured{ false },
    isEnd{ false },
    isHint{ false }
{
    _window.setKeyRepeatEnabled(false);
    _window.setFramerateLimit(30);

    initImages();
    initSounds();
    initText();

    generateGameObjects();

    _currentObject.setOutlineColor(sf::Color::Blue);
    _currentObject.setFillColor(sf::Color::Transparent);
    _currentObject.setPosition(280.f, 103.f);
    _currentObject.setOutlineThickness(5.f);
	
}

const bool Game::isRunning() const
{
	return _window.isOpen();
}

void Game::update()
{
    pollEvents();

    if(isEnd && !endSwitcher)
    {
        switchEndGame();
    }

}

void Game::render()
{
    _window.clear();
    drawGameObjects();
    _window.display();

}

void Game::checkEndGame()
{

    for (size_t i = 0; i < _gameObjects[0].size(); ++i)
    {
        if(_gameObjects[0][i]._logoType!=Logo::BARCA
            || _gameObjects[2][i]._logoType != Logo::JUVE 
            || _gameObjects[4][i]._logoType != Logo::PSG)
        {
            return;
        }
    }
    isEnd = true;
}

void Game::initSounds()
{
    _soundBuff.resize(5);
    _soundBuff[0].loadFromFile("sounds/switch.wav");
    _soundBuff[1].loadFromFile("sounds/block.wav");
    _soundBuff[2].loadFromFile("sounds/capture.wav");
    _soundBuff[3].loadFromFile("sounds/uncapture.wav");
    _soundBuff[4].loadFromFile("sounds/endgame.flac");

    _sounds.resize(_soundBuff.size());

    for (size_t i = 0; i < _soundBuff.size(); ++i)
    {
        _sounds[i].setBuffer(_soundBuff[i]);

    }

    _soundtrack.openFromFile("sounds/Instrumental.ogg");
    _soundtrack.setLoop(true);
    _soundtrack.setVolume(70);


}

void Game::initImages()
{
    _backgroundImage.loadFromFile("images/game background.png");
    _background.setTexture(_backgroundImage);

    _hintImage.loadFromFile("images/hint.png");
    _hint.setTexture(_hintImage);
}

void Game::initText()
{
    _font.loadFromFile("fonts/Quinoa.ttf");

    _endTextFirstStr.setFont(_font);
    _endTextFirstStr.setCharacterSize(60);
    _endTextFirstStr.setOutlineColor(sf::Color::Black);
    _endTextFirstStr.setOutlineThickness(4.f);
    _endTextFirstStr.setPosition(25.f, 300.f);

    _endTextSecondStr = _endTextFirstStr;
    _endTextSecondStr.setString((L"Нажмите esc для выхода"));
    _endTextSecondStr.setPosition(150.f, 400.f);

}

void Game::switchEndGame()
{
    _soundtrack.stop();
    _sounds[4].play();

    _endTextFirstStr.setString((L"Игра пройдена за " + std::to_wstring((int)(_clock.getElapsedTime().asSeconds() / 60)) 
        + L" минут " + std::to_wstring((int)(_clock.getElapsedTime().asSeconds()) - (int)(_clock.getElapsedTime().asSeconds() / 60)*60) + L" секунд"));
    endSwitcher = !endSwitcher;
  
}

void Game::musicPlay()
{
    _soundtrack.play();
}

Game::Logo::Logo():_logoType{ EMPTY }
{

    _logosImage.loadFromFile("images/logos.png");
    _logoSprite.setTexture(_logosImage);
    _logoSprite.setTextureRect(sf::IntRect(400, 0, 100, 100));
    _logoSprite.setPosition(0, 0);

}

void Game::Logo::changeLogoType(LogoType logoType, size_t rowsPos, size_t colsPos)
{
    _logoType = logoType;
    _logoSprite.setTextureRect(sf::IntRect(0+100* (int)_logoType, 0, 100, 100));
    _logoSprite.setPosition(280.f+100.f*colsPos, 103.f+100.f*rowsPos);

}
