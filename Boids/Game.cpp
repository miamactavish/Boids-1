/*

---- NOTE FROM MS. MIA: ----


The code in this file is used to create the graphics window and draw the boids on the screen. You do NOT need
to modify, read, or understand this file! But you're free to poke around in it if you'd like. :)
If you change something in this file and things end up breaking, redownload the code from Schoology!

*/



#include "Flock.h"
#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define BOID_AMOUNT 50

// Construct window using SFML
Game::Game()
{
	//this->boidsSize = rand() % 10 - 3;
	this->_window_height = 768;
	this->_window_width = 1204;
	this->_window.create(sf::VideoMode(_window_width, _window_height), "Boids");
	this->_window.setFramerateLimit(60);
	printInstructions();
}

// Run the simulation. Run creates the boids that we'll display, checks for user
// input, and updates the view
void Game::Run()
{
	for (int i = 0; i < BOID_AMOUNT; i++) {
		createBoid(_window_width / 2, _window_height / 2, sf::Color::Green, sf::Color::Blue);
	}

	sf::Font font;
	font.loadFromFile("consola.ttf");

	sf::Text fpsText("Frames per Second: ", font);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setCharacterSize(12);
	fpsText.setPosition(_window_width - 162, 0);

	sf::Text boidText("Total Boid Count: " + to_string(flock.getSize()), font);
	boidText.setFillColor(sf::Color::White);
	boidText.setCharacterSize(12);
	boidText.setPosition(_window_width - 155, 12);
	
	// Extra debug messages... you may want to add the methods getDesSep(), etc. and uncomment these lines! 
	
	sf::Text dSepText;// ("Separation Amount: " + to_string(flock.getBoid(0).getDesSep()), font);
	dSepText.setFillColor(sf::Color::White);
	dSepText.setCharacterSize(12);
	dSepText.setPosition(_window_width - 162, 60);

	sf::Text dAliText;// ("Alignment Amount: " + to_string(flock.getBoid(0).getDesAli()), font);
	dAliText.setFillColor(sf::Color::White);
	dAliText.setCharacterSize(12);
	dAliText.setPosition(_window_width - 155, 72);

	sf::Text dCohText;// ("Cohesion Amount: " + to_string(flock.getBoid(0).getDesCoh()), font);
	dCohText.setFillColor(sf::Color::White);
	dCohText.setCharacterSize(12);
	dCohText.setPosition(_window_width - 148, 84);

	sf::Text dSepWText;// ("Separation Weight: " + to_string(flock.getBoid(0).getSepW()), font);
	dSepWText.setFillColor(sf::Color::White);
	dSepWText.setCharacterSize(12);
	dSepWText.setPosition(_window_width - 162, 108);

	sf::Text dAliWText;// ("Alignment Weight: " + to_string(flock.getBoid(0).getAliW()), font);
	dAliWText.setFillColor(sf::Color::White);
	dAliWText.setCharacterSize(12);
	dAliWText.setPosition(_window_width - 155, 120);

	sf::Text dCohWText;// ("Cohesion Weight: " + to_string(flock.getBoid(0).getCohW()), font);
	dCohWText.setFillColor(sf::Color::White);
	dCohWText.setCharacterSize(12);
	dCohWText.setPosition(_window_width - 148, 132);
	

	// Clock added to calculate frame rate
	sf::Clock clock;

	while (_window.isOpen()) {
		float currentTime = clock.restart().asSeconds();
		float fps = 1 / currentTime; // 1 / refresh time = estimate of fps
		HandleInput();
		Render(fpsText, fps, boidText, 
				dSepText, dAliText, dCohText, dSepWText, dAliWText, dCohWText);
	}
}

void Game::HandleInput()
{
	sf::Event event;
	while (_window.pollEvent(event)) {
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
			_window.close();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5)
		{
			_window.close();
			Game temp;;
			temp.Run();
		}
	}
}

void Game::createBoid(float x, float y, sf::Color fillColor, sf::Color outlineColor)
{
	// Size of each individual boid
	int size = 5;

	Boid b(x, y);
	sf::CircleShape shape(size, 3);
	shape.setPosition(x, y);
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(.5);

	// FOV would show the radius that the boid would check to apply flocking

	//if (predStatus)
	//{
		sf::CircleShape FOV(20);
		FOV.setOutlineColor(sf::Color::White);
		FOV.setOutlineThickness(1);
		FOV.setFillColor(sf::Color::Transparent);
		FOVs.push_back(FOV);
	//}
	
	

	flock.addBoid(b);
	shapes.push_back(shape);

	// New Shape is drawn
	_window.draw(shapes[shapes.size() - 1]);
}

//Method of passing text needs refactoring
void Game::Render(sf::Text fpsText, float fps, sf::Text boidText, 
				sf::Text dSepText, sf::Text dAliText, sf::Text dCohText, sf::Text dSepWText, sf::Text dAliWText, sf::Text dCohWText)
{
	_window.clear();

	//Updating and drawing text can possibly be put in it's own function as well
	fpsText.setString("Frames per Second: " + to_string(int(fps + 0.5)));
	_window.draw(fpsText);

	boidText.setString("Total Boid Count: " + to_string(flock.getSize()));
	_window.draw(boidText);

	/*
	dSepText.setString("Separation Amount: " + to_string(int(flock.getBoid(0).getDesSep() + 0.5)));
	_window.draw(dSepText);

	dAliText.setString("Alignment Amount: " + to_string(int(flock.getBoid(0).getDesAli() + 0.5)));
	_window.draw(dAliText);

	dCohText.setString("Cohesion Amount: " + to_string(int(flock.getBoid(0).getDesCoh() + 0.5)));
	_window.draw(dCohText);

	dSepWText.setString("Separation Weight: " + to_string(flock.getBoid(0).getSepW()));
	_window.draw(dSepWText);

	dAliWText.setString("Alignment Weight: " + to_string(flock.getBoid(0).getAliW()));
	_window.draw(dAliWText);

	dCohWText.setString("Cohesion Weight: " + to_string(flock.getBoid(0).getCohW()));
	_window.draw(dCohWText);
	*/

	// Draws all of the Boids out, and applies functions that are needed to update.
	for (int i = 0; i < shapes.size(); i++) {
		_window.draw(shapes[i]);

		// Drawing and updating of the boids FOV
		//if (flock.getBoid(i).predatorStatus())
		//{
			//_window.draw(FOVs[i]);
			FOVs[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);
			FOVs[i].move(-25, -25);
		//}
		


		//cout << "Boid "<< i <<" Coordinates: (" << shapes[i].getPosition().x << ", " << shapes[i].getPosition().y << ")" << endl;
		//cout << "Boid Code " << i << " Location: (" << flock.getBoid(i).location.x << ", " << flock.getBoid(i).location.y << ")" << endl;

		// Matches up the location of the shape to the boid
		shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		float theta = flock.getBoid(i).getAngle(flock.getBoid(i).velocity);
		shapes[i].setRotation(theta);
	}

	// Applies the three rules to each boid in the flock and changes them accordingly.
	flock.flocking();

	_window.display();
}

void Game::printInstructions()
{
	cout << string(100, '\n');
	cout << "--------------Instructions--------------" << endl;
	cout << "Press 'F5' to restart the simulation" << endl;
	cout << "Press 'Esc', 'Backspace', or 'X' to Quit" << endl;
}