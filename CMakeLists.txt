# Kill the Retards 
# Copyright (C) 2022 jacekpoz
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
# 
# You should have received a copy of the GNU Affero General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME kill-the-enemies)

project(
	${PROJECT_NAME} VERSION 0.0.1
	DESCRIPTION "the most stupid game you've ever seen"
	LANGUAGES CXX
)

# flags taken from https://stackoverflow.com/questions/399850/best-compiler-warning-level-for-c-c-compilers/401276#401276
# and modified to my own liking and shit =D
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O -Wall -pedantic \
    -pedantic-errors -Wextra -Wcast-align \
    -Wcast-qual -Wchar-subscripts -Wcomment \
    -Wdisabled-optimization -Werror -Wfloat-equal -Wformat -Wformat=2 \
    -Wformat-nonliteral -Wformat-security -Wformat-y2k \
    -Wimport -Winit-self -Winvalid-pch \
    -Wunsafe-loop-optimizations -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute \
    -Wmissing-include-dirs -Wmissing-noreturn \
    -Wpacked -Wparentheses -Wpointer-arith \
    -Wredundant-decls -Wreturn-type \
    -Wsequence-point -Wshadow -Wsign-compare  -Wstack-protector \
    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch \
    -Wtrigraphs -Wuninitialized \
    -Wunknown-pragmas -Wunreachable-code -Wunused \
    -Wunused-function -Wunused-label -Wno-unused-parameter \
    -Wunused-value -Wunused-variable -Wvariadic-macros \
    -Wvolatile-register-var -Wwrite-strings \
	-lpthread \
	-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio")

find_package(SFML 2 REQUIRED COMPONENTS system window graphics audio)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Game.cpp
	src/systems/AISystem.cpp
	src/systems/AudioSystem.cpp
	src/systems/CameraSystem.cpp
	src/systems/CollisionXSystem.cpp
	src/systems/CollisionYSystem.cpp
	src/systems/DebugMenuSystem.cpp
	src/systems/DestroySystem.cpp
	src/systems/HealthRenderingSystem.cpp
	src/systems/HealthSystem.cpp
	src/systems/HitboxRenderingSystem.cpp
	src/systems/MovementXSystem.cpp
	src/systems/MovementYSystem.cpp
	src/systems/PlayerMovementSystem.cpp
	src/systems/RenderingSystem.cpp
	src/systems/SpriteRenderingSystem.cpp
	src/systems/System.cpp
	src/systems/WeaponRenderingSystem.cpp
	src/systems/WeaponSystem.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "lib/entt/src")
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json sfml-system sfml-window sfml-graphics sfml-audio)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
