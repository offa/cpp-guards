/*
 * Cpp-Guards - RAII classes
 * Copyright (C) 2016-2017  offa
 *
 * This file is part of Cpp-Guards.
 *
 * Cpp-Guards is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cpp-Guards is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cpp-Guards.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <utility>

namespace guards
{

    template<class Function>
    class ScopeGuard
    {
    public:

        explicit ScopeGuard(Function&& fn) : m_function(std::move_if_noexcept(fn))
        {
        }

        ~ScopeGuard()
        {
            m_function();
        }


    private:

        Function m_function;
    };


    template<class Function>
    constexpr ScopeGuard<Function> makeScopeGuard(Function&& fn) noexcept
    {
        return ScopeGuard<Function>(std::forward<Function>(fn));
    }

}

