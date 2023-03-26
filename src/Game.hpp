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

#pragma once

#include "systems/systems.hpp"
#include "Config.hpp"

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include <entt/entt.hpp>

class Game {
public:
	Game(sf::VideoMode mode, std::string title, uint32_t style);
			
	void handleEvent();
	void update(const float deltaTime);
	void render(const float deltaTime);
	
	void pause();
	void resume();
	void togglePause();

	void unfocus();
	void focus();
	
	bool isRunning();

	void addSystem(std::unique_ptr<System> s);
	void addRenderingSystem(std::unique_ptr<RenderingSystem> rs);
	
private:
	sf::RenderWindow window;
	entt::registry registry;

	Config conf;

	std::vector<std::unique_ptr<System>> systems;

	std::vector<std::unique_ptr<RenderingSystem>> renderingSystems;

	bool isPaused = false;
	bool isFocused = true;

	void pauseSystems();
	void resumeSystems();
};

