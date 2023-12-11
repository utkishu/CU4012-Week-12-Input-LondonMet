#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	circle.setRadius(20);
	circle.setFillColor(sf::Color::Red);
	
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W)) {
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed" << std::endl;
	}
	
	if ((input->isKeyDown(sf::Keyboard::J)) && (input->isKeyDown(sf::Keyboard::K)) && (input->isKeyDown(sf::Keyboard::L))) {
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "J,K, and L were pressed" << std::endl;
	}

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		input->setKeyUp(sf::Keyboard::Escape);

		window->close();
	}


	mousePositionText.setString("Mouse Position:");
	sf::Vector2i MousePos = sf::Vector2i(input->getMouseX(), input->getMouseY());

	std::string MousePosString = std::to_string(MousePos.x);
	MousePosString.append(":");
	MousePosString.append(std::to_string(MousePos.y));
	mousePositionText.setString(MousePosString);


	if (input->isMouseLDown()) {
		if (!Dragging) {

			Dragging = true;
			InitialMousePosition = sf::Vector2i(input->getMouseX(), input->getMouseY());
		}
		else {
			FinalMousePosition = sf::Vector2i(input->getMouseX(), input->getMouseY());

			float dx = float(FinalMousePosition.x - InitialMousePosition.x);
			float dy = float(FinalMousePosition.y - InitialMousePosition.y);
			float distance = std::sqrt((dx * dx) + (dy * dy));

			std::cout << "Distance: " << distance << std::endl;
		}
	}
	else {
		Dragging = false;
	}





	if (input->isMouseRDown()) {
		const int CirPosX = input->getMouseX();
		const int CirPosY = input->getMouseY();
		circle.setPosition(CirPosX - 20, CirPosY - 20);
	}
}

// Update game objects
void Level::update()
{
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "error loading font" << std::endl;
	};

	mousePositionText.setFont(font);
	mousePositionText.setCharacterSize(24);
	mousePositionText.setFillColor(sf::Color::Red);
	

}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(mousePositionText);
	window->draw(circle);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}