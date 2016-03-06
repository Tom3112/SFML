#include "stdafx.h"
#include "Game.h"

class Game
{
	enum Direction { S, A, D, W };
	public:
		sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
		sf::Vector2i source = sf::Vector2i (1, S);
		Game::Game() :
			mWindow(sf::VideoMode(1920, 1080), "SFML Application", sf::Style::Fullscreen),
			view(sf::FloatRect(0, 0, 1920, 1080)),
			mBackground(),
			mPlayer() {
				mWindow.setView(view);
				if (!bgTexture.loadFromFile("background.jpg"))
					std::cout << "Error" << std::endl;
				mBackground.setTexture(bgTexture);
				if (!pTexture.loadFromFile("player.png"))
					std::cout << "Error" << std::endl;
				mPlayer.setTexture(pTexture);
				//LoadPlayerTexture(pTexture, sf::IntRect(32, 0, 32, 32));
	};
	void Game::run()
	{
		mWindow.setKeyRepeatEnabled(false);
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (mWindow.isOpen())
		{
			processEvents();
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processEvents();
				update(TimePerFrame);
			}
			render();
		}
	}
private:
	bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false, mIsMovingRight = false, mIsRight = false, mIsLeft = false;
	float PlayerSpeed = 125;
	void Game::processEvents()
	{
		sf::Clock clock;
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			source.x++;
			if (source.x * 32 >= pTexture.getSize().x)
				source.x = 0;
			if (event.type == sf::Event::Closed)
				mWindow.close();
			switch (event.type)
			{
				case sf::Event::KeyPressed:
					handlePlayerInput(event.key.code, true);
					break;
				case sf::Event::KeyReleased:
					handlePlayerInput(event.key.code, false);
					break;
				case sf::Event::MouseButtonPressed:
					handlePlayerInput(event.mouseButton.button, true);
					break;
				case sf::Event::MouseButtonReleased:
					handlePlayerInput(event.mouseButton.button, false);
					break;
				case sf::Event::Closed:
					mWindow.close();
					break;
			}
		}
	}
	void Game::handlePlayerInput(sf::Keyboard::Key key,
		bool isPressed)
	{
		if (key == sf::Keyboard::W) {
			mIsMovingUp = isPressed;
			if (isPressed) {
				source.y = W;
			}
		}
		else if (key == sf::Keyboard::S) {
			mIsMovingDown = isPressed;
			if (isPressed) {
				source.y = S;
			}
		}
		else if (key == sf::Keyboard::D) {
			mIsMovingRight = isPressed;
			if (isPressed);
				source.y = D;
		}
		else if (key == sf::Keyboard::A) {
			mIsMovingLeft = isPressed;
			if (isPressed);
				source.y = A;
		}
		else if (key == sf::Keyboard::Escape)
			mWindow.close();
	}
	void Game::handlePlayerInput(sf::Mouse::Button key, bool isPressed)
	{
		if (key == sf::Mouse::Left)
			mIsLeft = isPressed;
		if (key == sf::Mouse::Right)
			mIsRight = isPressed;
	}
	void Game::update(sf::Time deltaTime)
	{
		sf::Vector2f movement(0.f, 0.f);
		if (mIsMovingUp) {
			movement.y -= PlayerSpeed;
			view.move(sf::Vector2f(0, -1));
		}
		if (mIsMovingDown) {
			movement.y += PlayerSpeed;
			view.move(sf::Vector2f(0, 1));
		}
		if (mIsMovingLeft) {
			movement.x -= PlayerSpeed;
			view.move(sf::Vector2f(-1, 0));
		}
		if (mIsMovingRight) {
			movement.x += PlayerSpeed;
			view.move(sf::Vector2f(1,0));
		}
		mPlayer.move(movement * deltaTime.asSeconds());

	}
	void Game::render()
	{
		mPlayer.setTextureRect(sf::IntRect(source.x * 32 , source.y * 32, 32, 32));
		mWindow.clear();
		mWindow.draw(mBackground);
		mWindow.draw(mPlayer);
		mWindow.setView(view);
		mWindow.display();
	}
	private:
		sf::RenderWindow mWindow;
		sf::Sprite mPlayer;
		sf::Texture bgTexture;
		sf::Texture pTexture;
		sf::Sprite mBackground;
		sf::View view;
};


int main()
{
	Game game;
	game.run();
	return 0;
}
