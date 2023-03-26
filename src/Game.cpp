// Kill the Retards 
// Copyright (C) 2022 jacekpoz
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
// 
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "Game.hpp"

#include "components/components.hpp"
#include "helpers/helpers.hpp"
#include "math.hpp"

#include <iostream>
#include <random>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

Game::Game(sf::VideoMode mode, std::string title, uint32_t style) : isPaused(false) {
	window.create(mode, title, style);

	if (!conf.font.loadFromFile("res/fonts/AldotheApache.ttf"))
		std::cout << "font not found\n";
	
	conf.vsync = true;
	conf.debug = false;
	conf.telescope = true;

	// the order of those matters at least in the respective systems
	// for an example you could move all of the rendering systems below
	// the normal systems and shit would work the same
	auto srs = std::make_unique<SpriteRenderingSystem>(registry, conf, window);
	addRenderingSystem(std::move(srs));

	auto wrs = std::make_unique<WeaponRenderingSystem>(registry, conf, window);
	addRenderingSystem(std::move(wrs));

	auto hers = std::make_unique<HealthRenderingSystem>(registry, conf, window);
	addRenderingSystem(std::move(hers));

	auto cas = std::make_unique<CameraSystem>(registry, conf, window);
	addRenderingSystem(std::move(cas));

	auto hirs = std::make_unique<HitboxRenderingSystem>(registry, conf, window);
	addRenderingSystem(std::move(hirs));

	auto dms = std::make_unique<DebugMenuSystem>(registry, conf, window, systems, renderingSystems);
	addRenderingSystem(std::move(dms));

	auto ws = std::make_unique<WeaponSystem>(registry, conf);
	addSystem(std::move(ws));

	auto pms = std::make_unique<PlayerMovementSystem>(registry, conf);
	addSystem(std::move(pms));

	auto ais = std::make_unique<AISystem>(registry, conf);
	addSystem(std::move(ais));

	auto mxs = std::make_unique<MovementXSystem>(registry, conf);
	addSystem(std::move(mxs));

	auto cxs = std::make_unique<CollisionXSystem>(registry, conf);
	addSystem(std::move(cxs));

	auto mys = std::make_unique<MovementYSystem>(registry, conf);
	addSystem(std::move(mys));

	auto cys = std::make_unique<CollisionYSystem>(registry, conf);
	addSystem(std::move(cys));

	auto hs = std::make_unique<HealthSystem>(registry, conf);
	addSystem(std::move(hs));

	auto as = std::make_unique<AudioSystem>(registry, conf);
	addSystem(std::move(as));

	// should always be at the end
	auto ds = std::make_unique<DestroySystem>(registry, conf);
	addSystem(std::move(ds));
	
 	auto weapon = ktr::createWeapon(registry, 2.f, 0.25f, "res/images/weapons/deagle.png");
 	
	/*auto player = */ktr::createPlayer(registry, sf::Vector2f(500.f, 500.f), 500.f, 250.f, 20.f, "res/images/player.png", 32.f, weapon);

	std::random_device rnd;
	std::mt19937 gen(rnd());
	std::uniform_real_distribution<> distr(100, 300);

	for (int i = 0; i < 10; ++i) {
		sf::Vector2f pos(static_cast<float>(distr(gen)), static_cast<float>(distr(gen)));
		/*auto enemy = */ktr::createEnemy(registry, pos, 150.f, 50.f, 20.f, "res/images/enemy.png", 32.f);
	}

	auto ground = registry.create();
	registry.emplace<Sprite>(ground, "res/images/ground.png");
	registry.emplace<Surface>(ground, sf::FloatRect(0.f, 0.f, static_cast<float>(mode.width), static_cast<float>(mode.height)));
	registry.emplace<Friction>(ground, 0.f, 100.f);

 	for (float i = 1.f; i <= 9.f; i += 1.f) 
		/*auto wall = */ktr::createWall(registry, sf::Vector2f(i * 64.f, 64.f), 64.f, 64.f, "res/images/wall.png");
}

void Game::handleEvent() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:{
				window.close();
			}break;
			case sf::Event::LostFocus:{
				unfocus();
			}break;
			case sf::Event::GainedFocus:{
				focus();
			}break;
			case sf::Event::Resized:{
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}break;
			case sf::Event::KeyPressed:{
				switch (event.key.code) {
					case sf::Keyboard::G:{
						conf.debug = !conf.debug;
					}break;
					case sf::Keyboard::P:{
						togglePause();
					}break;
					case sf::Keyboard::V:{
						conf.vsync = !conf.vsync;
						window.setVerticalSyncEnabled(conf.vsync);
					}break;
					case sf::Keyboard::T:{
						conf.telescope = !conf.telescope;
					}break;
					default: break;
				}
			}break;
			default: break;
		}
	}
}

void Game::update(const float deltaTime) {
	
	for (auto &s : systems) 
		s->update(deltaTime);
}

void Game::render(const float deltaTime) {
	window.clear(sf::Color::Black);

	for (auto &rs : renderingSystems) 
		rs->update(deltaTime);

	window.display();
}

void Game::pause() {
	isPaused = true;
	pauseSystems();
}

void Game::resume() {
	isPaused = false;
	resumeSystems();
}

void Game::togglePause() {
	if (isPaused) {
		resume();
	} else {
		pause();
	}
}

void Game::unfocus() {
	isFocused = false;
	if (!isPaused) pauseSystems();
}

void Game::focus() {
	isFocused = true;
	if (!isPaused) resumeSystems();
}

bool Game::isRunning() {
	return window.isOpen();
}

void Game::addSystem(std::unique_ptr<System> s) {
	systems.push_back(std::move(s));
}

void Game::addRenderingSystem(std::unique_ptr<RenderingSystem> rs) {
	renderingSystems.push_back(std::move(rs));
}

void Game::pauseSystems() {
	for (auto &s : systems) 
		s->pause();
	for (auto &rs: renderingSystems) 
		rs->pause();
}

void Game::resumeSystems() {
	for (auto &s : systems) 
		s->resume();
	for (auto &rs : renderingSystems) 
		rs->resume();
}

