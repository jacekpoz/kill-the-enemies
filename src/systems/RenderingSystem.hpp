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

#include "System.hpp"

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <entt/entt.hpp>

class RenderingSystem : public System {

public:
	RenderingSystem(entt::registry &r, Config &c, sf::RenderWindow &w);

	void update(const float deltaTime) = 0;
	
protected:
	sf::RenderWindow &window;

	std::unordered_map<std::string, sf::Texture> txCache;
	sf::Texture &getTexture(const std::string path);

	std::unordered_map<entt::entity, sf::Sprite> sprCache;
	sf::Sprite &getSprite(const entt::entity entity);
};

