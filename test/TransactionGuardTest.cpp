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

#include "guards/TransactionGuard.h"
#include "TestCommon.h"
#include <memory>

using namespace guards;

class TransactionGuardTest : public testing::Test
{
protected:

    void SetUp() override
    {
        rollbackMock = std::make_unique<ExecutionMock>();
    }

    void TearDown() override
    {
    }


    std::unique_ptr<ExecutionMock> rollbackMock;
};


TEST_F(TransactionGuardTest, rollbackOnDestruction)
{
    EXPECT_CALL(*rollbackMock, execute()).Times(1);

    {
        auto fn = [&] { rollbackMock->execute(); };
        TransactionGuard<decltype(fn)> guard(fn);
        unused(guard);
    }
}

TEST_F(TransactionGuardTest, rollbackIfNoCommit)
{
    EXPECT_CALL(*rollbackMock, execute()).Times(1);

    {
        auto guard = makeTransactionGuard([&] { rollbackMock->execute(); });
        unused(guard);
    }
}

TEST_F(TransactionGuardTest, rollbackIfNoCommitBeforeException)
{
    EXPECT_CALL(*rollbackMock, execute()).Times(1);

    {
        auto guard = makeTransactionGuard([&] { rollbackMock->execute(); });
        unused(guard);
        EXPECT_THROW(throw int(3), int);
    }
}

TEST_F(TransactionGuardTest, noRollbackIfCommit)
{
    EXPECT_CALL(*rollbackMock, execute()).Times(0);

    {
        auto guard = makeTransactionGuard([&] { rollbackMock->execute(); });
        guard.commit();
    }
}

TEST_F(TransactionGuardTest, noRollbackIfCommitBeforeException)
{
    EXPECT_CALL(*rollbackMock, execute()).Times(0);

    {
        auto guard = makeTransactionGuard([&] { rollbackMock->execute(); });
        guard.commit();
        EXPECT_THROW(throw int(3), int);
    }
}

TEST_F(TransactionGuardTest, commitSetsStae)
{
    auto guard = makeTransactionGuard([&] { rollbackMock->execute(); });
    EXPECT_FALSE(guard.isCommited());
    guard.commit();
    EXPECT_TRUE(guard.isCommited());
}

TEST_F(TransactionGuardTest, makeTransactionGuard)
{
    EXPECT_CALL(*rollbackMock, execute()).Times(1);

    {
        auto guard = makeTransactionGuard([&] { rollbackMock->execute(); });
        unused(guard);
    }
}

