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

#include "RenderingSystem.hpp"

#include <iostream>

RenderingSystem::RenderingSystem(entt::registry &r, Config &c, sf::RenderWindow &w) 
	: System(r, c), window(w) {}

sf::Texture &RenderingSystem::getTexture(const std::string path) {

	if (txCache.find(path) == txCache.end()) {
		sf::Texture tx;
		if (!tx.loadFromFile(path)) {
			// TODO some fuckin logger idk man
			std::cout << path << " not found!!!\n";
		}
		txCache[path] = tx;
	}

	return txCache[path];
}

sf::Sprite &RenderingSystem::getSprite(const entt::entity entity) {

	if (sprCache.find(entity) == sprCache.end()) {
		auto sprite = registry.get<Sprite>(entity);
		
		sf::Sprite spr;
		spr.setTexture(getTexture(sprite.path));

		sprCache[entity] = spr;
	}

	return sprCache[entity];
}

