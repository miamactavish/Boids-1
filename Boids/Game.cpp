#include "Flock.h"
#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define BOID_AMOUNT 50


// Construct window using SFML
Game::Game()
{
	this->boidsSize = 5.0;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	this->window_height = desktop.height;
	this->window_width = desktop.width;
	this->window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
}

// Run the simulation. Run creates the boids that we'll display, checks for user
// input, and updates the view
void Game::Run()
{
	for (int i = 0; i < BOID_AMOUNT; i++) {
		createBoid(window_width / 2, window_height / 2, false, sf::Color::Green, sf::Color::Blue);
	}

	sf::Font font;
	font.loadFromFile("consola.ttf");

	sf::Text fpsText("Frames per Second: ", font);
	fpsText.setColor(sf::Color::White);
	fpsText.setCharacterSize(12);
	fpsText.setPosition(window_width - 162, 0);

	sf::Text preyText("Total Prey Count: " + to_string(flock.preyCount()), font);
	preyText.setColor(sf::Color::White);
	preyText.setCharacterSize(12);
	preyText.setPosition(window_width - 155, 12);

	sf::Text predText("Total Predator Count: " + to_string(flock.predCount()), font);
	predText.setColor(sf::Color::White);
	predText.setCharacterSize(12);
	predText.setPosition(window_width - 183, 24);

	sf::Text boidText("Total Boid Count: " + to_string(flock.getSize()), font);
	boidText.setColor(sf::Color::White);
	boidText.setCharacterSize(12);
	boidText.setPosition(window_width - 155, 36);
	
	sf::Text dSepText("Separation Amount: " + to_string(flock.getBoid(0).getDesSep()), font);
	dSepText.setColor(sf::Color::White);
	dSepText.setCharacterSize(12);
	dSepText.setPosition(window_width - 162, 60);

	sf::Text dAliText("Alignment Amount: " + to_string(flock.getBoid(0).getDesAli()), font);
	dAliText.setColor(sf::Color::White);
	dAliText.setCharacterSize(12);
	dAliText.setPosition(window_width - 155, 72);

	sf::Text dCohText("Cohesion Amount: " + to_string(flock.getBoid(0).getDesCoh()), font);
	dCohText.setColor(sf::Color::White);
	dCohText.setCharacterSize(12);
	dCohText.setPosition(window_width - 148, 84);

	sf::Text dSepWText("Separation Weight: " + to_string(flock.getBoid(0).getSepW()), font);
	dSepWText.setColor(sf::Color::White);
	dSepWText.setCharacterSize(12);
	dSepWText.setPosition(window_width - 162, 108);

	sf::Text dAliWText("Alignment Weight: " + to_string(flock.getBoid(0).getAliW()), font);
	dAliWText.setColor(sf::Color::White);
	dAliWText.setCharacterSize(12);
	dAliWText.setPosition(window_width - 155, 120);

	sf::Text dCohWText("Cohesion Weight: " + to_string(flock.getBoid(0).getCohW()), font);
	dCohWText.setColor(sf::Color::White);
	dCohWText.setCharacterSize(12);
	dCohWText.setPosition(window_width - 148, 132);

	sf::Clock clock;
	float lastTime = 0;

	while (window.isOpen()) {
		float currentTime = clock.restart().asSeconds();
		float fps = 1 / currentTime;
		HandleInput();
		Render(fpsText, fps, preyText, predText, boidText, 
				dSepText, dAliText, dCohText, dSepWText, dAliWText, dCohWText);

		lastTime = currentTime;
	}
}

void Game::HandleInput()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		// "close requested" event: we close the window
		// Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)
		if ((event.type == sf::Event::Closed) ||
			(event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Escape) ||
			(event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::BackSpace) ||
			(event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::X))
		{
			window.close();
		}

		// Event to create new "prey" boids
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Space) {
			//createBoid(window_width / 2, window_height / 2, false, sf::Color::Green, sf::Color::Blue);
			createBoid(rand() % window_width, rand() % window_height, false, sf::Color::Green, sf::Color::Blue);
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Q)
		{
			flock.addDesSep();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::A)
		{
			flock.subDesSep();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::W)
		{
			flock.addDesAli();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::S)
		{
			flock.subDesAli();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::E)
		{
			flock.addDesCoh();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::D)
		{
			flock.subDesCoh();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::I)
		{
			flock.addSepW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::J)
		{
			flock.subSepW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::O)
		{
			flock.addAliW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::K)
		{
			flock.subAliW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::P)
		{
			flock.addCohW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::L)
		{
			flock.subCohW();
		}
	}

	// Check for mouse click, draws and adds boid to flock if so.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// Gets mouse coordinates, sets that as the location of the boid and the shape
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
		createBoid(mouseCoords.x, mouseCoords.y, true, sf::Color::Red, sf::Color::Red);
	}
}

void Game::createBoid(float x, float y, bool predStatus, sf::Color fillColor, sf::Color outlineColor)
{
	Boid b(x, y, predStatus);
	sf::CircleShape shape(20, 3);
	shape.setPosition(x, y);
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(.5);
	shape.setRadius(boidsSize);

	flock.addBoid(b);
	shapes.push_back(shape);

	// New Shape is drawn
	window.draw(shapes[shapes.size() - 1]);
}

void Game::Render(sf::Text fpsText, float fps, sf::Text preyText, sf::Text predText, sf::Text boidText, 
				sf::Text dSepText, sf::Text dAliText, sf::Text dCohText, sf::Text dSepWText, sf::Text dAliWText, sf::Text dCohWText)
{
	window.clear();

	fpsText.setString("Frames per Second: " + to_string(int(fps + 0.5)));
	window.draw(fpsText);

	preyText.setString("Total Prey Count: " + to_string(flock.preyCount()));
	window.draw(preyText);

	predText.setString("Total Predator Count: " + to_string(flock.predCount()));
	window.draw(predText);

	boidText.setString("Total Boid Count: " + to_string(flock.getSize()));
	window.draw(boidText);

	dSepText.setString("Separation Amount: " + to_string(int(flock.getBoid(0).getDesSep() + 0.5)));
	window.draw(dSepText);

	dAliText.setString("Alignment Amount: " + to_string(int(flock.getBoid(0).getDesAli() + 0.5)));
	window.draw(dAliText);

	dCohText.setString("Cohesion Amount: " + to_string(int(flock.getBoid(0).getDesCoh() + 0.5)));
	window.draw(dCohText);

	dSepWText.setString("Separation Weight: " + to_string(flock.getBoid(0).getSepW()));
	window.draw(dSepWText);

	dAliWText.setString("Alignment Weight: " + to_string(flock.getBoid(0).getAliW()));
	window.draw(dAliWText);

	dCohWText.setString("Cohesion Weight: " + to_string(flock.getBoid(0).getCohW()));
	window.draw(dCohWText);

	// Draws all of the Boids out, and applies functions that are needed to update.
	for (int i = 0; i < shapes.size(); i++) {
		window.draw(shapes[i]);

		//cout << "Boid "<< i <<" Coordinates: (" << shapes[i].getPosition().x << ", " << shapes[i].getPosition().y << ")" << endl;
		//cout << "Boid Code " << i << " Location: (" << flock.getBoid(i).location.x << ", " << flock.getBoid(i).location.y << ")" << endl;

		// Matches up the location of the shape to the boid
		shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		float theta = flock.getBoid(i).getAngle(flock.getBoid(i).velocity);
		shapes[i].setRotation(theta);

		// Prevent boids from moving off the screen through wrapping
		// If boid exits right boundary
		if (shapes[i].getPosition().x > window_width)
			shapes[i].setPosition(shapes[i].getPosition().x - window_width, shapes[i].getPosition().y);
		// If boid exits bottom boundary
		if (shapes[i].getPosition().y > window_height)
			shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - window_height);
		// If boid exits left boundary
		if (shapes[i].getPosition().x < 0)
			shapes[i].setPosition(shapes[i].getPosition().x + window_width, shapes[i].getPosition().y);
		// If boid exits top boundary
		if (shapes[i].getPosition().y < 0)
			shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + window_height);
	}

	// Applies the three rules to each boid in the flock and changes them accordingly.
	flock.flocking();

	window.display();
}