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

#include "SpriteRenderingSystem.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

SpriteRenderingSystem::SpriteRenderingSystem(entt::registry &r, Config &c, sf::RenderWindow &w) 
	: RenderingSystem(r, c, w) {}

void SpriteRenderingSystem::update(const float deltaTime) {

	const auto surfaceView = registry.view<Surface, Sprite>();

	for (const auto surface : surfaceView) {
		const auto [surf, sprite] = surfaceView.get(surface);

		sf::Texture &surfTx = getTexture(sprite.path);
		surfTx.setRepeated(true);

		sf::Sprite &spr = getSprite(surface);
		
		const sf::IntRect sprRect(
			static_cast<int>(surf.rect.left), 
			static_cast<int>(surf.rect.top), 
			static_cast<int>(surf.rect.width), 
			static_cast<int>(surf.rect.height)
		);
		spr.setTextureRect(sprRect);

		window.draw(spr);
	}

	const auto renderableView = registry.view<Position, Sprite>();
	for (const auto entity : renderableView) {
		const auto [pos, sprite] = renderableView.get(entity);
			
		sf::Sprite &spr = getSprite(entity);

		// sets sprite origin to the center of the texture
		const sf::FloatRect bounds = spr.getLocalBounds();
		const sf::Vector2f origin{
			bounds.width / 2.f,
			bounds.height / 2.f
		};
		spr.setOrigin(origin);

		spr.setPosition(pos.x, pos.y);
		spr.setRotation(sprite.angle);
		spr.setScale(sf::Vector2f(sprite.scaleX, sprite.scaleY));
		
		window.draw(spr);
	}
}

