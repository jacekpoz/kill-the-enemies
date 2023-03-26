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

#include "System.hpp"

// this is only for entt::entity but I don't know which header that's in
#include <entt/entt.hpp>

class CollisionYSystem : public System {

public:
	CollisionYSystem(entt::registry &r, Config &c);

	void update(const float deltaTime) override;
private:
	void resolveCollisionY(const entt::entity e1, const entt::entity e2, const float deltaTime);

	void movableImmovableY(const entt::entity m, const entt::entity i, const float deltaTime);

 	// specific collisions
 	void projectileCollision(const entt::entity proj, const entt::entity e, const float deltaTime);
	void playerEnemyCollision(const entt::entity pl, const entt::entity e, const float deltaTime);
};

