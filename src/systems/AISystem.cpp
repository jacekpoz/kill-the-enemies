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

#include "AISystem.hpp"

#include "../math.hpp"

#include <cmath>

#include <SFML/System/Vector2.hpp>

AISystem::AISystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void AISystem::update(const float deltaTime) {
	if (paused) return;

	const auto enemies = registry.view<Enemy>();
	const auto players = registry.view<Player>();
	
	for (const auto enemy : enemies) {
		const auto enemyPos = registry.get<Position>(enemy);
		sf::Vector2f closestDist{-1.f, -1.f};
			
		for (const auto player : players) {
			const auto playerPos = registry.get<Position>(player);
		
			sf::Vector2f dist(enemyPos.x - playerPos.x, enemyPos.y - playerPos.y);
			if (closestDist.x <= -1.f && closestDist.y <= -1.f) closestDist = dist;
			float distLen = std::sqrt(dist.x * dist.x + dist.y * dist.y);
			float closestDistLen = std::sqrt(closestDist.x * closestDist.x + closestDist.y * closestDist.y);
			if (distLen < closestDistLen) closestDist = dist;
		}
	
		sf::Vector2f distNorm = normalize(closestDist);
		registry.patch<Sprite>(enemy, [distNorm](auto &spr) {
			if (distNorm.x > 0) {
				spr.scaleX = -1.f;
			} else if (distNorm.x < 0) {
				spr.scaleX = 1.f;
			}
		});
			
		registry.patch<Acceleration>(enemy, [distNorm, deltaTime](auto &a) {
			a.x -= distNorm.x;
			a.y -= distNorm.y;
		});
	} 
}

