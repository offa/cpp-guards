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

#ifndef TRANSACTIONGUARD_H
#define TRANSACTIONGUARD_H

namespace guards
{

    template<class Function>
    class TransactionGuard final
    {
    public:

        explicit TransactionGuard(Function rollback) : m_rollback(rollback), m_commited(false)
        {
        }

        ~TransactionGuard()
        {
            if( m_commited == false )
            {
                m_rollback();
            }
        }

        void commit()
        {
            m_commited = true;
        }

        bool isCommited() const
        {
            return m_commited;
        }


    private:

        const Function m_rollback;
        bool m_commited;
    };


    template<class Function>
    constexpr TransactionGuard<Function> makeTransactionGuard(Function rollback)
    {
        return TransactionGuard<Function>(rollback);
    }

}

#endif /* TRANSACTIONGUARD_H */
