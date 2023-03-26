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

#include "HitboxRenderingSystem.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

HitboxRenderingSystem::HitboxRenderingSystem(entt::registry &r, Config &c, sf::RenderWindow &w) 
	: RenderingSystem(r, c, w) {}

void HitboxRenderingSystem::update(const float deltaTime) {

	if (!conf.debug) return;

	const auto entities = registry.view<Position, Hitbox, Sprite>();

	for (const auto entity : entities) {
		const auto [pos, hitbox, sprite] = registry.get<Position, Hitbox, Sprite>(entity);

		sf::Sprite &spr = getSprite(entity);

		const sf::FloatRect bounds = spr.getLocalBounds();
		const sf::Vector2f localCenter{
			bounds.left + bounds.width / 2.f,
			bounds.top + bounds.height / 2.f
		};

		if (hitbox.isRect) {
			const Rect r = std::get<Rect>(hitbox.rect);
			sf::RectangleShape rect;
			rect.setOrigin(localCenter);
			rect.setPosition(pos.x, pos.y);
			rect.setSize(sf::Vector2f(r.w, r.h));
			rect.setScale(sf::Vector2f(sprite.scaleX, sprite.scaleY));
			rect.setRotation(sprite.angle);
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(1);
			window.draw(rect);
		} else if (!hitbox.isRect) {
			const Circ c = std::get<Circ>(hitbox.circ);
			sf::CircleShape circ;
			circ.setOrigin(localCenter);
			circ.setPosition(pos.x, pos.y);
			circ.setRadius(c.r);
			circ.setScale(sf::Vector2f(sprite.scaleX, sprite.scaleY));
			circ.setRotation(sprite.angle);
			circ.setFillColor(sf::Color::Transparent);
			circ.setOutlineColor(sf::Color::White);
			circ.setOutlineThickness(1);
			window.draw(circ);
		}
	}
}

