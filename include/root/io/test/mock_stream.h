/*
 * Copyright (C) 2020  Fernando Escribano Macias 
 *
 * This file is part of the Root Engine.
 * 
 * The Root Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Root Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Root Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <root/io/stream.h>

#include <gmock/gmock.h>

namespace root {
class mock_stream : public stream {
public:
    MOCK_METHOD(value_or_error<u64>, read, (void*, const u64&));
    MOCK_METHOD(value_or_error<u64>, write, (const void*, const u64&));
    MOCK_METHOD(error, seek, (const i64&, const relative_to&));
    MOCK_METHOD(value_or_error<i64>, tell, (const relative_to&), (const));
};
} // namespace root