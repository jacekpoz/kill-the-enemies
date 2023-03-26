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

#include "CollisionXSystem.hpp"

#include "../math.hpp"

CollisionXSystem::CollisionXSystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void CollisionXSystem::update(const float deltaTime) {
	if (paused) return;

	const auto movables = registry.view<Movable, Hitbox, Position>();
	const auto immovables = registry.view<Immovable, Hitbox, Position>();

	for (const auto m : movables) {
 		const auto [mHitbox, mPos] = registry.get<Hitbox, Position>(m);

		for (const auto mm : movables) {
			const auto [mmHitbox, mmPos] = registry.get<Hitbox, Position>(mm);
			if (collides(mHitbox, mPos, mmHitbox, mmPos)) 
				resolveCollisionX(m, mm, deltaTime);
		}
		for (const auto i : immovables) {
			const auto [iHitbox, iPos] = registry.get<Hitbox, Position>(i);
			if (collides(mHitbox, mPos, iHitbox, iPos)) 
				resolveCollisionX(m, i, deltaTime);
		}
	}
}

void CollisionXSystem::resolveCollisionX(const entt::entity e1, const entt::entity e2, const float deltaTime) {
	if (e1 == e2) return;

 	if (registry.all_of<Projectile>(e1)) {
 		projectileCollision(e1, e2, deltaTime);
 		return;
 	}
 	if (registry.all_of<Projectile>(e2)) {
 		projectileCollision(e2, e1, deltaTime);
 		return;
 	}
	if (registry.all_of<Player>(e1) && registry.all_of<Enemy>(e2)) {
		playerEnemyCollision(e1, e2, deltaTime);
	}
	if (registry.all_of<Player>(e2) && registry.all_of<Enemy>(e1)) {
		playerEnemyCollision(e2, e1, deltaTime);
	}
 
	if (registry.all_of<Movable>(e1) && registry.all_of<Movable>(e2)) {
		const auto [e1Pos, e1Hitbox, e1Vel] = registry.get<Position, Hitbox, Velocity>(e1);
		const auto [e2Pos, e2Hitbox, e2Vel] = registry.get<Position, Hitbox, Velocity>(e2);
		
		registry.patch<Velocity>(e1, [deltaTime, e1Pos, e2Pos](auto &vel) {
			vel.x -= (e2Pos.x - e1Pos.x) * deltaTime * 25.f;
		});
		registry.patch<Velocity>(e2, [deltaTime, e1Pos, e2Pos](auto &vel) {
			vel.x += (e2Pos.x - e1Pos.x) * deltaTime * 25.f;
		});
	}

	if (registry.all_of<Movable>(e1) && registry.all_of<Immovable>(e2)) 
		movableImmovableX(e1, e2, deltaTime);
	if (registry.all_of<Immovable>(e1) && registry.all_of<Movable>(e2)) 
		movableImmovableX(e2, e1, deltaTime);
}

void CollisionXSystem::movableImmovableX(const entt::entity m, const entt::entity i, const float deltaTime) {
	if (m == i) return;

 	if (!registry.all_of<Movable>(m)) return;
 	if (!registry.all_of<Immovable>(i)) return;

	registry.patch<Position>(m, [](auto &p) { p.x = p.lastX; });
	registry.patch<Velocity>(m, [](auto &v) { v.x = 0.f; });
	registry.patch<Acceleration>(m, [](auto &a) { a.x = 0.f; });
}

void CollisionXSystem::projectileCollision(const entt::entity proj, const entt::entity e, const float deltaTime) {
	if (proj == e) return;
	if (!registry.all_of<Projectile>(proj)) return;
	if (registry.all_of<Projectile>(e)) return;

	const auto projectile = registry.get<Projectile>(proj);

	if (projectile.owner == e) return;
	if (registry.all_of<Health>(e)) {
		registry.patch<Health>(e, [projectile](auto &h) {
			h.collides = true;
			h.damage = projectile.damage;
		});
	}

	registry.patch<Health>(proj, [](auto &h) {
		h.collides = true;
		h.damage = 1.f;
	});
}

void CollisionXSystem::playerEnemyCollision(const entt::entity pl, const entt::entity e, const float deltaTime) {
	registry.patch<Health>(pl, [](auto &h) {
		h.collides = true;
		h.damage = 1.f;
	});
}

