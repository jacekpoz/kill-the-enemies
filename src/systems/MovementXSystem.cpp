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

#include "MovementXSystem.hpp"

MovementXSystem::MovementXSystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void MovementXSystem::update(const float deltaTime) {
	if (paused) return;

	const auto movers = registry.view<Position, Velocity, Acceleration>();

	for (const auto entity : movers) {
		auto [p, v, a] = registry.get<Position, Velocity, Acceleration>(entity);

		// if has health it resets its collides flag, same in MovementYSystem
		if (registry.all_of<Health>(entity)) 
			registry.patch<Health>(entity, [](auto &h) { h.collides = false; });

		if (a.x > a.maxX) a.x = a.maxX;
		if (a.x < -a.maxX) a.x = -a.maxX;

		v.x += a.x * deltaTime;

		if (v.x > v.maxX) v.x = v.maxX;
		if (v.x < -v.maxX) v.x = -v.maxX;

		p.lastX = p.x;

		p.x += v.x * deltaTime;
	}
}

