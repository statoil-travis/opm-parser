/*
  Copyright (C) 2014 by Andreas Lauser

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OPM_PARSER_PLYMAX_TABLE_HPP
#define	OPM_PARSER_PLYMAX_TABLE_HPP

#include "SimpleTable.hpp"

namespace Opm {
    // forward declaration
    class TableManager;

    class PlymaxTable : public SimpleTable {
    public:
        friend class TableManager;
        PlymaxTable() = default;

        /*!
         * \brief Read the PLYMAX keyword and provide some convenience
         *        methods for it.
         */
        void init(Opm::DeckRecordConstPtr record)
        {
            createColumns(std::vector<std::string>{"C_POLYMER", "C_POLYMER_MAX"});
            for (size_t colIdx = 0; colIdx < record->size(); colIdx++) {
                auto item = record->getItem( colIdx );
                m_columns[colIdx].push_back( item->getSIDouble(0) );
                m_valueDefaulted[colIdx].push_back( item->defaultApplied(0) );
            }
            SimpleTable::checkNonDefaultable("C_POLYMER");
            SimpleTable::checkMonotonic("C_POLYMER", /*isAscending=*/false);
            SimpleTable::checkNonDefaultable("C_POLYMER_MAX");
            SimpleTable::checkMonotonic("C_POLYMER_MAX", /*isAscending=*/false);
        }

        using SimpleTable::numTables;
        using SimpleTable::numRows;
        using SimpleTable::numColumns;
        using SimpleTable::evaluate;

        const std::vector<double> &getPolymerConcentrationColumn() const
        { return SimpleTable::getColumn(0); }

        const std::vector<double> &getMaxPolymerConcentrationColumn() const
        { return SimpleTable::getColumn(1); }
    };
}

#endif
