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

#include "WeaponRenderingSystem.hpp"

#include <cmath>

#include <SFML/Window/Mouse.hpp>

WeaponRenderingSystem::WeaponRenderingSystem(entt::registry &r, Config &c, sf::RenderWindow &w) 
	: RenderingSystem(r, c, w) {}

void WeaponRenderingSystem::update(const float deltaTime) {
	if (paused) return;

	const auto players = registry.view<Player>();

	for (const auto player : players) {
		auto [playerPos, playerHitbox, playerSprite] = registry.get<Position, Hitbox, Sprite>(player);
		auto pl = registry.get<Player>(player);
		auto [weaponPos, weaponSprite] = registry.get<Position, Sprite>(pl.weapon);

		sf::Vector2f mP = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// mouse position relative to the player
		float relativeX = mP.x - playerPos.x;
		float relativeY = mP.y - playerPos.y;

		if (relativeX < 0.f) {
			weaponSprite.scaleY = -1.f;
			playerSprite.scaleX = -1.f;
		} else if (relativeX > 0.f) {
			weaponSprite.scaleY = 1.f;
			playerSprite.scaleX = 1.f;
		}

		// angle from player to cursor
		float angleRad = static_cast<float>(std::atan2(relativeX, relativeY));

		// angle in degrees, I subtracted it from 360 because doo doo fart
		// SDL's (0, 0) point is top left of the window so I had to subtract it from 360 I think
		float angleDeg = 360.f - (angleRad * (180.f / PI));

		// adjust angle due to texture being wrong
		float angleDegAdjusted = angleDeg + 90.f;
		weaponSprite.angle = angleDegAdjusted;

		// change angle back to radians cause we need it later
		float angleRadAdjusted = angleDegAdjusted / (180.f / PI);

		float r = std::get<Circ>(playerHitbox.circ).r;

		// hypotenuse of a triangle, of which 2 sides are the radii of the circle
		float hypotenuse = static_cast<float>(std::sqrt(r * r * 2.f));

		// some weird fucking shit but it lines up almost perfectly to the player
		float weirdShit = hypotenuse + r / 2.f;

		// cos and sin are used to convert the angle back into the length of the sides when multiplied with the monstrosity
		weaponPos.x = playerPos.x + (weirdShit * std::cos(angleRadAdjusted));
		weaponPos.y = playerPos.y + (weirdShit * std::sin(angleRadAdjusted));

	}
}

