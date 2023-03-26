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

#include "WeaponSystem.hpp"

#include <cmath>
#include <iostream>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Keyboard.hpp>

WeaponSystem::WeaponSystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void WeaponSystem::update(const float deltaTime) {
	if (paused) return;
	
	const auto players = registry.view<Player>();

	for (const auto player : players) {
		const auto pl = registry.get<Player>(player);
		const auto [weapon, wPos, wSprite] = registry.get<Weapon, Position, Sprite>(pl.weapon);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (weapon.cooldownTimer > 0.f) continue;

			auto proj = registry.create();
			registry.emplace<Projectile>(proj, weapon.damage, player);
			registry.emplace<Movable>(proj);
			registry.emplace<Position>(proj, wPos.x, wPos.y);
			registry.emplace<Health>(proj, 1.f, 1.f, 1.f);

			float projAngleRad = wSprite.angle / (180.f / PI);
			registry.emplace<Velocity>(proj, std::cos(projAngleRad) * 500.f, std::sin(projAngleRad) * 500.f, 500.f, 500.f);

			registry.emplace<Acceleration>(proj, 0.f, 0.f, 0.f, 0.f);
			Hitbox projH;
			projH.isRect = true;
			Rect projRect;
			projRect.w = 20.f;
			projRect.h = 10.f;
			projH.rect = projRect;
			registry.emplace<Hitbox>(proj, projH);
			Sprite projSprite;
			projSprite.path = "res/images/bullet.png";
			projSprite.angle = wSprite.angle;
			registry.emplace<Sprite>(proj, projSprite);

			registry.patch<Weapon>(pl.weapon, [](auto &w) { w.cooldownTimer = w.cooldown; });

			registry.emplace_or_replace<Audio>(proj, "res/sounds/shoot.wav", true);
			
		} else {
			registry.patch<Weapon>(pl.weapon, [deltaTime](auto &w) {
				w.cooldownTimer -= deltaTime;
				if (w.cooldownTimer < 0.f) w.cooldownTimer = 0.f;
			});
		}
	}
}

