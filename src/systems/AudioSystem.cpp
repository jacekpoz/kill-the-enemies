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

#include "AudioSystem.hpp"

#include <iostream>

AudioSystem::AudioSystem(entt::registry &r, Config &c) 
	: System(r, c) {}

void AudioSystem::update(const float deltaTime) {
	
	const auto audioPlayers = registry.view<Audio>();

	for (const auto entity : audioPlayers) {
		auto &audio = registry.get<Audio>(entity);

		if (!audio.play) continue;

		getSound(entity).play();

		audio.play = false;

		registry.patch<Audio>(entity);
	}
}

sf::SoundBuffer &AudioSystem::getSoundBuffer(const std::string path) {
	if (sndBfrCache.find(path) == sndBfrCache.end()) {
		sf::SoundBuffer sb;
		if (!sb.loadFromFile(path)) {
			// TODO LOGGER !!!!
			std::cout << path << " not found!!!\n";
		}
		sndBfrCache[path] = sb;
	}

	return sndBfrCache[path];
}

sf::Sound &AudioSystem::getSound(const entt::entity entity) {
	if (sndCache.find(entity) == sndCache.end()) {
		const auto audio = registry.get<Audio>(entity);

		sf::Sound s;
		s.setBuffer(getSoundBuffer(audio.audio));
		sndCache[entity] = s;
	}

	return sndCache[entity];
}

