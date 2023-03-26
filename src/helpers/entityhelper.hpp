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

#include <SFML/System/Vector2.hpp>

#include <entt/entt.hpp>

#define DEFAULT_HEALTH_COOLDOWN 0.01f

namespace ktr {
	entt::entity createHumanoid(entt::registry &r, const sf::Vector2f pos, const float maxVel, const float maxAccel, const float health, const std::string tex, const float radius) {
		const auto humanoid = r.create();

		r.emplace<Movable>(humanoid);
		r.emplace<Position>(humanoid, pos.x, pos.y);
		r.emplace<Velocity>(humanoid, 0.f, 0.f, maxVel, maxVel);
		r.emplace<Acceleration>(humanoid, 0.f, 0.f, maxAccel, maxAccel);
		r.emplace<Sprite>(humanoid, tex);
		Hitbox humanoidH;
		humanoidH.isRect = false;
		Circ humanoidCirc;
		humanoidCirc.r = radius;
		humanoidH.circ = humanoidCirc;
		r.emplace<Hitbox>(humanoid, humanoidH);

		return humanoid;
	}

	entt::entity createPlayer(entt::registry &r, const sf::Vector2f pos, const float maxVel, const float maxAccel, const float health, const std::string tex, const float radius, const entt::entity weapon) {	
		const auto player = createHumanoid(r, pos, maxVel, maxAccel, health, tex, radius);

		r.emplace<Health>(player, health, health, 1.f);
		r.emplace<Player>(player, weapon);

		return player;
	}

	entt::entity createEnemy(entt::registry &r, const sf::Vector2f pos, const float maxVel, const float maxAccel, const float health, const std::string tex, const float radius) {
		const auto enemy = createHumanoid(r, pos, maxVel, maxAccel, health, tex, radius);

		r.emplace<Health>(enemy, health, health, DEFAULT_HEALTH_COOLDOWN);
		r.emplace<Enemy>(enemy);

		return enemy;
	}

	entt::entity createWeapon(entt::registry &r, const float damage, const float cooldown, const std::string tex) {
		const auto weapon = r.create();

		r.emplace<Weapon>(weapon, damage, cooldown);
		r.emplace<Sprite>(weapon, tex);
		r.emplace<Position>(weapon, 0.f, 0.f);

		return weapon;
	}

	entt::entity createWall(entt::registry &r, const sf::Vector2f pos, const float width, const float height, const std::string tex) {
		const auto wall = r.create();

		r.emplace<Immovable>(wall);
		r.emplace<Position>(wall, pos.x, pos.y);
		Hitbox wallH;
		wallH.isRect = true;
		Rect wallRect;
		wallRect.w = width;
		wallRect.h = height;
		wallH.rect = wallRect;
		r.emplace<Hitbox>(wall, wallH);
		r.emplace<Sprite>(wall, tex);

		return wall;
	}
}

