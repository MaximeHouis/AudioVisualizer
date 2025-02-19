/*
 * Copyright (c) 2019 Rayé Maxime
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

// For Windows
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstddef>
#include <complex>
#include <array>
#include <valarray>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class AudioVisualizer final {
public:
    static constexpr size_t BUFFER_SIZE{8196};
    static constexpr double FREQ_MAX{62500};
private:
    using Complex = std::complex<double>;
    using ComplexArray = std::valarray<Complex>;

    const sf::Sound &_sound;
    const sf::SoundBuffer &_buffer;

    ComplexArray _array{};
    std::array<double, BUFFER_SIZE> _scaleList{};

    struct SoundBufferData {
        decltype(_buffer.getChannelCount()) channelCount;
        decltype(_buffer.getSampleCount()) sampleCount;
        decltype(_buffer.getSampleRate()) sampleRate;

        SoundBufferData(decltype(_buffer.getChannelCount()) channelCount,
                        decltype(_buffer.getSampleCount()) sampleCount,
                        decltype(_buffer.getSampleRate()) sampleRate)
            : channelCount{channelCount}, sampleCount{sampleCount}, sampleRate{sampleRate}
        {}
    };

    struct VisualizationData {
        const double scaleAverage{0};
        const decltype(_scaleList) *scaleList{};
    };

    const SoundBufferData _bufferData;

    void _fastFourierTransform(decltype(_array) &array);

    static void _smoothArray(decltype(_scaleList) &data);

public:
    AudioVisualizer(decltype(_sound) sound, decltype(_buffer) buffer);

    AudioVisualizer(const AudioVisualizer &) = delete;
    AudioVisualizer &operator=(const AudioVisualizer &) = delete;

    VisualizationData getVisualizationData();
};