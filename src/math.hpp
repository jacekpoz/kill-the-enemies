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

#include "components/components.hpp"
#include "utils.hpp"

#include <cmath>

#include <SFML/System/Vector2.hpp>

inline float length(const sf::Vector2f v) {
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

// stolen from https://en.sfml-dev.org/forums/index.php?topic=1488.0
inline sf::Vector2f normalize(const sf::Vector2f v) {
	float len = length(v);
	if (len <= 0.f) 
		return sf::Vector2f(v.x / len, v.y / len);
	return v;
}

// pls don't use
inline bool _collides(const Circ c, const Position pc, const Rect r, const Position pr) {
	// stolen from https://stackoverflow.com/questions/21089959/detecting-collision-of-rectangle-with-circle
	float distX = std::abs(pc.x - pr.x);
	float distY = std::abs(pc.y - pr.y);

	if (distX > (r.w / 2.f + c.r)) return false;
	if (distY > (r.h / 2.f + c.r)) return false;
	if (distX <= (r.w / 2.f)) return true;
	if (distY <= (r.h / 2.f)) return true;

	float dx = distX - r.w / 2.f;
	float dy = distY - r.h / 2.f;
	return dx * dx + dy * dy <= c.r * c.r;
}

inline bool collides(const Hitbox h1, const Position p1, const Hitbox h2, const Position p2) {
	if (!h1.isRect && !h2.isRect) {
		const Circ circ1 = std::get<Circ>(h1.circ);
		const Circ circ2 = std::get<Circ>(h2.circ);
		const float dist = length(sf::Vector2f(p2.x - p1.x, p2.y - p1.y));
		return dist <= circ1.r + circ2.r;
	}
	if (h1.isRect && h2.isRect) {
		const Rect rect1 = std::get<Rect>(h1.rect);
		const Rect rect2 = std::get<Rect>(h2.rect);
		return ((p1.x + rect1.w / 2.f) >= (p2.x - rect2.w / 2.f)) && 
			((p1.x - rect1.w / 2.f) <= (p2.x + rect2.w / 2.f)) && 
			((p1.y + rect1.h / 2.f) >= (p2.y - rect2.h / 2.f)) && 
			((p1.y - rect1.h / 2.f) <= (p2.y + rect2.h / 2.f));
	}
	if (h1.isRect && !h2.isRect) return _collides(std::get<Circ>(h2.circ), p2, std::get<Rect>(h1.rect), p1);
	if (!h1.isRect && h2.isRect) return _collides(std::get<Circ>(h1.circ), p1, std::get<Rect>(h2.rect), p2);
	return false;
}

