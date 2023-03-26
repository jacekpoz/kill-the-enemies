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

#include "CameraSystem.hpp"

#include <cmath>

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

CameraSystem::CameraSystem(entt::registry &r, Config &c, sf::RenderWindow &w) 
	: RenderingSystem(r, c, w) {}

void CameraSystem::update(const float deltaTime) {
	if (paused) return;

	const auto players = registry.view<Player>();

	for (const auto player : players) {
		const auto pos = registry.get<Position>(player);

		sf::Vector2f mP = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		float relativeX = mP.x - pos.x;
		float relativeY = mP.y - pos.y;

		sf::View telescopeView(sf::Vector2f(pos.x + relativeX * 0.15f, pos.y + relativeY * 0.15f), window.getView().getSize());
		sf::View normalView(sf::Vector2f(pos.x, pos.y), window.getView().getSize());

		if (!conf.telescope) window.setView(normalView);
		else window.setView(telescopeView);
	}
}

