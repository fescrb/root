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

#include <root/core/primitives.h>

#include <functional>
#include <utility>

namespace root {

template<typename cointainer_t, 
         typename index_t = i64,
         typename element_t = decltype(std::declval<cointainer_t>()[std::declval<index_t>()]), 
         std::function<index_t(const index_t)> next_f = [](const index_t i){return ++i;}, 
         std::function<index_t(const index_t)> prev_f = [](const index_t i){return --i;}>
class linear_iterator {
public:
    using mutable_element = std::remove_const_t<element_t>;
    using const_element = std::add_const_t<element_t>;

    

protected:
    container_t& m_container;
    index_t index;
};

} // namespace root