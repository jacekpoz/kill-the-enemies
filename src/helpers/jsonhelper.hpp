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

#include "../components/components.hpp"
#include "entityhelper.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include <entt/entt.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// IDK what to do with this

namespace ktr {

	void dumpSave(const entt::registry &r, const std::string file) {
//		json j;
//
//        entt::snapshot{r}.entities(j);
//
//		std::ofstream s;
	}

	void loadSave(entt::registry &r, const std::string file) {
		
	}
}

