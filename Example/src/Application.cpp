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

#include <iostream>
#include "Application.hpp"

Application::Application()
    : _window{sf::VideoMode{1280, 720}, _title}
{
    _window.setVerticalSyncEnabled(true);

    if (!_soundBuffer.loadFromFile("assets/ignite.ogg"))
        throw std::runtime_error{"Failed to load music."};

    _music.setBuffer(_soundBuffer);
    _music.setLoop(true);
    _music.play();

    _visualizer = std::make_unique<AudioVisualizer>(_music, _soundBuffer);

    constexpr float circleSize = 42;
    _tmpCircle.setFillColor(sf::Color::Yellow);
    _tmpCircle.setRadius(circleSize);
    _tmpCircle.setOrigin(circleSize, circleSize);
}

void Application::_pollEvents()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
}

void Application::_update()
{
    auto scale = _visualizer->getVisualizationData().scaleAverage;

    _tmpCircle.setPosition(_window.getSize().x / 2.0f, _window.getSize().y / 2.0f);
    _tmpCircle.setScale(scale, scale);
}

void Application::_render()
{
    _window.clear();

    _window.draw(_tmpCircle);

    _window.display();
}

void Application::run()
{
    sf::Clock clock;

    while (_window.isOpen()) {
        _pollEvents();
        _update();
        _render();
        _updateFramerate();

        _deltaTime = clock.restart().asSeconds();
    }
}

void Application::_updateFramerate()
{
    static decltype(_framerate) frameCount = 0;
    static sf::Clock clock;

    ++frameCount;

    if (clock.getElapsedTime().asSeconds() >= 1) {
        _framerate = frameCount;
        frameCount = 0;
        clock.restart();

        _window.setTitle(_title + " - " + std::to_string(_framerate) + " fps");
    }
}
