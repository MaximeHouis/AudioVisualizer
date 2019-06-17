/*
 * Copyright (c) 2019 Houis Maxime
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

#include "../../AudioVisualizer.hpp"

class Application {
private:
    const std::string _title{"SFML Audio Visualizer"};

    sf::RenderWindow _window;
    sf::Event _event{};
    sf::Sound _music{};
    sf::SoundBuffer _soundBuffer{};

    sf::CircleShape _tmpCircle{};

    double _deltaTime{0};
    size_t _framerate{0};
    std::unique_ptr<AudioVisualizer> _visualizer{nullptr};

    void _pollEvents();
    void _update();
    void _render();
    void _updateFramerate();
public:
    Application();

    void run();
};

