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

#include "DestroySystem.hpp"

#include <iostream>

#include <SFML/Audio/Sound.hpp>

DestroySystem::DestroySystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void DestroySystem::update(const float deltaTime) {
	if (paused) return;

	const auto healthy = registry.view<Health>();

	for (const auto entity : healthy) {
		const auto h = registry.get<Health>(entity);

		if (!h.alive) {

			if (registry.all_of<Player>(entity)) {
				registry.destroy(registry.get<Player>(entity).weapon);
			}
			registry.destroy(entity);
		}
	}
}

