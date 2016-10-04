/*
 * Cpp-Guards - RAII classes
 * Copyright (C) 2016  offa
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

template<class T>
constexpr void unused(T&&) { }


struct ExecutionMock
{
    MOCK_METHOD0(execute, void());
};

