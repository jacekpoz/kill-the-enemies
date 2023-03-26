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

#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

// contains globally available things that are gonna change during playtime
// passed as reference to each system's constructor from the main game class

struct Config {
	// main font used throughout the game, more might be added
	sf::Font font;
	// yeah
	bool vsync;
	// yeah
	bool fullscren;
	// yeah
	bool debug;
	// volume percentages (0.0 - 1.0)
	float masterVolume;
	float musicVolume;
	float effectsVolume;
	// saved in this format: pl, en, de, es and so on
	std::string language;

	// {{{ player shit
	// the effect that moves the camera with your cursor
	bool telescope;
	// }}}
};

