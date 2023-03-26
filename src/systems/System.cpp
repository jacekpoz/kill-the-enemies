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

#include "System.hpp"

System::System(entt::registry &r, Config &c) 
	: registry(r), conf(c), paused(false) {}

bool System::isPaused() {
	return paused;
}

void System::pause() {
	paused = true;
}

void System::resume() {
	paused = false;
}

void System::togglePause() {
	if (!paused) pause();
	else if (paused) resume();
}

