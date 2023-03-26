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

#include "DebugMenuSystem.hpp"

#include <string>

#include <SFML/Graphics/Color.hpp>

DebugMenuSystem::DebugMenuSystem(entt::registry &r, Config &c, sf::RenderWindow &w, std::vector<std::unique_ptr<System>> &s, std::vector<std::unique_ptr<RenderingSystem>> &rs) 
	: RenderingSystem(r, c, w), systems(s), renderingSystems(rs) {}

void DebugMenuSystem::update(const float deltaTime) {
	if (!conf.debug) return;

	const int charSize = 16;

	// gamechanging method of calculating FPS created by krizej
	fpsText.setString("FPS: " + std::to_string(1.f / deltaTime));

	fpsText.setFont(conf.font);
	float fpsX = (window.getView().getCenter().x - window.getView().getSize().x / 2) + 10;
	float fpsY = (window.getView().getCenter().y - window.getView().getSize().y / 2) + 10;
	fpsText.setPosition(fpsX, fpsY);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setCharacterSize(charSize);

	const auto players = registry.view<Player>();

	for (const auto player : players) {
		const auto pos = registry.get<Position>(player);

		posText.setString("X: " + std::to_string(pos.x) + "; Y: " + std::to_string(pos.y) + ";");
	}

	posText.setFont(conf.font);
	posText.setPosition(fpsX, fpsY + charSize + 10.f);
	posText.setFillColor(sf::Color::White);
	posText.setCharacterSize(charSize);

	window.draw(fpsText);
	window.draw(posText);
}

