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

#include <string>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <entt/entt.hpp>

class AudioSystem : public System {
	
public:
	AudioSystem(entt::registry &r, Config &c);

	void update(const float deltaTime) override;

private:
	std::unordered_map<std::string, sf::SoundBuffer> sndBfrCache;
	sf::SoundBuffer &getSoundBuffer(const std::string path);

	std::unordered_map<entt::entity, sf::Sound> sndCache;
	sf::Sound &getSound(const entt::entity entity);
};

