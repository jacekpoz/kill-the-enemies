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

#include "PlayerMovementSystem.hpp"

#include <SFML/Window/Keyboard.hpp>

PlayerMovementSystem::PlayerMovementSystem(entt::registry &r, Config &c) : System(r, c) {}

void PlayerMovementSystem::update(const float deltaTime) {

	if (paused) return;

	auto playerView = registry.view<Player>();
	
	for (const auto player : playerView) {
		auto &a = registry.get<Acceleration>(player);
		auto &v = registry.get<Velocity>(player);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (a.y > 0.f) a.y = 0.f;
			a.y -= 1000.f;
			
			registry.patch<Acceleration>(player);
		} else {
			if (a.y < 0.f) {
				a.y += 200.f;
				if (a.y > 0.f) a.y = 0.f;
				
				registry.patch<Acceleration>(player);
			}
			if (v.y < 0.f) {
				v.y += 5.f;
				if (v.y > 0.f) v.y = 0.f;

				registry.patch<Velocity>(player);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (a.y < 0.f) a.y = 0.f;
			a.y += 1000.f;
			
			registry.patch<Acceleration>(player);
		} else {
			if (a.y > 0.f) {
				a.y -= 200.f;
				if (a.y < 0.f) a.y = 0.f;
				
				registry.patch<Acceleration>(player);
			}
			if (v.y > 0.f) {
				v.y -= 5.f;
				if (v.y < 0.f) v.y = 0.f;

				registry.patch<Velocity>(player);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (a.x > 0.f) a.x = 0.f;
			a.x -= 1000.f;
			
			registry.patch<Acceleration>(player);
		} else {
			if (a.x < 0.f) {
				a.x += 200.f;
				if (a.x > 0.f) a.x = 0.f;
				
				registry.patch<Acceleration>(player);
			}
			if (v.x < 0.f) {
				v.x += 5.f;
				if (v.x > 0.f) v.x = 0.f;

				registry.patch<Velocity>(player);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (a.x < 0.f) a.x = 0.f;
			a.x += 1000.f;
			
			registry.patch<Acceleration>(player);
		} else {
			if (a.x > 0.f) {
				a.x -= 200.f;
				if (a.x < 0.f) a.x = 0.f;
				
				registry.patch<Acceleration>(player);
			}
			if (v.x > 0.f) {
				v.x -= 5.f;
				if (v.x < 0.f) v.x = 0.f;

				registry.patch<Velocity>(player);
			}
		}
	}
}

