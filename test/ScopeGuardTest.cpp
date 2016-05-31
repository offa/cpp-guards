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

#include "guards/ScopeGuard.h"
#include "TestCommon.h"

using namespace guards;

class ScopeGuardTest : public testing::Test
{
protected:

    void SetUp() override
    {
        scopeMock = std::make_unique<ExecutionMock>();
    }

    void TearDown() override
    {
    }


    std::unique_ptr<ExecutionMock> scopeMock;
};

TEST_F(ScopeGuardTest, functionCalledOnDestruction)
{
    EXPECT_CALL(*scopeMock, execute()).Times(1);

    {
        auto fn = [&] { scopeMock->execute(); };
        ScopeGuard<decltype(fn)> guard(fn);
        UNUSED(guard);
    }
}

TEST_F(ScopeGuardTest, functionCalledOnException)
{
    EXPECT_CALL(*scopeMock, execute()).Times(1);

    {
        auto guard = makeScopeGuard([&] { scopeMock->execute(); });
        UNUSED(guard);
        EXPECT_THROW(throw int(3), int);
    }
}

TEST_F(ScopeGuardTest, makeScopeGuard)
{
    EXPECT_CALL(*scopeMock, execute()).Times(1);

    {
        auto guard = makeScopeGuard([&] { scopeMock->execute(); });
        UNUSED(guard);
    }
}

