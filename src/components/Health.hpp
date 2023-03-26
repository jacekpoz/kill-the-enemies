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

struct Health {
	float health, maxHealth;

	// constant value
	float cooldown;
	// actual counter
	float timeLeft = 0.f;

	// how much damage the thing that collided with this dealt
	float damage = 0.f;

	// collides with something that damages it
	bool collides = false;
	// in a state of being damaged - still on cooldown
	bool damaged = false;

	bool alive = true;
};
