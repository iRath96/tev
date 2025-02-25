/*
 * tev -- the EXR viewer
 *
 * Copyright (C) 2025 Thomas Müller <contact@tom94.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <tev/Channel.h>
#include <tev/Image.h>
#include <tev/ThreadPool.h>

#include <nanogui/vector.h>

#include <istream>
#include <string>

namespace tev {

class ImageLoader {
public:
    virtual ~ImageLoader() {}

    virtual bool canLoadFile(std::istream& iStream) const = 0;

    // Return loaded image data as well as whether that data has the alpha channel pre-multiplied or not.
    virtual Task<std::vector<ImageData>>
        load(std::istream& iStream, const fs::path& path, const std::string& channelSelector, int priority) const = 0;

    virtual std::string name() const = 0;

    static const std::vector<std::unique_ptr<ImageLoader>>& getLoaders();

protected:
    static std::vector<Channel> makeNChannels(int numChannels, const nanogui::Vector2i& size);
};

} // namespace tev
