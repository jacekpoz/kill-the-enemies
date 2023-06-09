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

#include "RenderingSystem.hpp"

class DebugRenderingSystem : public RenderingSystem {

public:
	DebugRenderingSystem(entt::registry &r, sf::RenderWindow &w);

	void update(const float deltaTime, const bool debug) override;

private:
	std::vector<std::unique_ptr<System>> systems;
	std::vector<std::unique_ptr<RenderingSystem>> renderingSystems;
};

