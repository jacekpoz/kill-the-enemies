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

#include "HealthSystem.hpp"

HealthSystem::HealthSystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void HealthSystem::update(const float deltaTime) {
	if (paused) return;
	
	const auto healthy = registry.view<Health>();

	for (const auto entity : healthy) {

		registry.patch<Health>(entity, [this, entity, deltaTime](auto &h) {
			if (h.health <= 0.f) {
				h.alive = false;
				if (!registry.all_of<Projectile>(entity)) {
					registry.emplace_or_replace<Audio>(entity, "res/sounds/death.wav", true);
				}
			}

			if (h.collides && !h.damaged) {
				h.health -= h.damage;
				h.damaged = true;
				h.timeLeft = h.cooldown;
			}

			if (h.damaged) {
				if (h.timeLeft <= 0.f) {
					h.timeLeft = 0.f;
					h.damaged = false;
				} else {
					h.timeLeft -= deltaTime;
				}
			}
		});

	}
}

