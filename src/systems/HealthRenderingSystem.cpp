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

#include "HealthRenderingSystem.hpp"

#include <iomanip>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

HealthRenderingSystem::HealthRenderingSystem(entt::registry &r, Config &c, sf::RenderWindow &w) 
	: RenderingSystem(r, c, w) {}

void HealthRenderingSystem::update(const float deltaTime) {
	
	const auto entities = registry.view<Health, Position, Hitbox>();

	for (const auto entity : entities) {
		const auto [health, pos, hitbox] = entities.get(entity);

		if (health.health >= health.maxHealth && !conf.debug) continue;

		const float fullBarWidth = hitbox.isRect ? std::get<Rect>(hitbox.rect).w : std::get<Circ>(hitbox.circ).r * 2.f;
		const float healthWidth = (health.health / health.maxHealth) * fullBarWidth;
		const float barHeight = 10.f;

		sf::RectangleShape healthBar;
		healthBar.setSize(sf::Vector2f(healthWidth, barHeight));
		healthBar.setPosition(pos.x - fullBarWidth / 2.f, pos.y - fullBarWidth - barHeight / 2.f);
		healthBar.setFillColor(sf::Color::Red);

		sf::RectangleShape outlineBar;
		outlineBar.setSize(sf::Vector2f(fullBarWidth, barHeight));
		outlineBar.setOrigin(outlineBar.getSize() / 2.f);
		outlineBar.setPosition(pos.x, pos.y - fullBarWidth);
		outlineBar.setOutlineColor(sf::Color::White);
		outlineBar.setFillColor(sf::Color::Transparent);
		outlineBar.setOutlineThickness(2.f);

		std::ostringstream healthText;
		healthText << std::fixed;
		healthText << std::setprecision(0);
		healthText << health.health << " / " << health.maxHealth;

		sf::Text debugText(healthText.str(), conf.font, barHeight);
		debugText.setFillColor(sf::Color::White);
		debugText.setOrigin(debugText.getLocalBounds().left + debugText.getLocalBounds().width / 2.f, debugText.getLocalBounds().top + debugText.getLocalBounds().height / 2.f);
		debugText.setPosition(outlineBar.getPosition());

		window.draw(healthBar);
		window.draw(outlineBar);
		window.draw(debugText);
	}
}

