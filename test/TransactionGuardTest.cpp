/*
 * Cpp-Guards - RAII classes
 * Copyright (C) 2016-2019  offa
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

#include "guards/TransactionGuard.h"
#include "TestCommon.h"

using namespace guards;
using namespace trompeloeil;

namespace
{
    ExecutionMock m;

    void execute()
    {
        m.execute();
    }
}


TEST_CASE("rollbackOnDestruction", "[TransactionGuard]")
{
    REQUIRE_CALL(m, execute());

    {
        auto guard = makeTransactionGuard(execute);
        unused(guard);
    }
}

TEST_CASE("rollback if not commited", "[TransactionGuard]")
{
    REQUIRE_CALL(m, execute());

    {
        auto guard = makeTransactionGuard(execute);
        unused(guard);
    }
}

TEST_CASE("rollback if not commited before exception", "[TransactionGuard]")
{
    REQUIRE_CALL(m, execute());

    {
        auto guard = makeTransactionGuard(execute);
        unused(guard);
        REQUIRE_THROWS(throw int{3});
    }
}

TEST_CASE("no rollback if commited", "[TransactionGuard]")
{
    REQUIRE_CALL(m, execute()).TIMES(0);

    {
        auto guard = makeTransactionGuard(execute);
        guard.commit();
    }
}

TEST_CASE("no rollback if commited before exception", "[TransactionGuard]")
{
    REQUIRE_CALL(m, execute()).TIMES(0);

    {
        auto guard = makeTransactionGuard(execute);
        guard.commit();
        REQUIRE_THROWS(throw int{3});
    }
}

TEST_CASE("commit sets state", "[TransactionGuard]")
{
    auto guard = makeTransactionGuard(execute);
    CHECK_FALSE(guard.isCommited());
    guard.commit();
    CHECK(guard.isCommited());
}

