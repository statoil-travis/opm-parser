/*
  Copyright 2015 Statoil ASA.

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

#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/Deck/DeckItem.hpp>
#include <opm/parser/eclipse/Deck/DeckKeyword.hpp>
#include <opm/parser/eclipse/Deck/DeckRecord.hpp>
#include <opm/parser/eclipse/EclipseState/InitConfig/InitConfig.hpp>

#include <iostream>

namespace Opm {

    InitConfig::InitConfig(DeckConstPtr deck) {
        m_restartInitiated = false;
        m_restartStep = 0;
        m_restartRootName = "";

        initRestartKW(deck);
    }

    void InitConfig::initRestartKW(DeckConstPtr deck) {
        if (deck->hasKeyword("RESTART") && deck->hasKeyword("SKIPREST")) {
            DeckKeywordConstPtr restart_kw = deck->getKeyword("RESTART");
            DeckRecordConstPtr restart_dataRecord = restart_kw->getRecord(0);
            DeckItemPtr restart_rootname_item = restart_dataRecord->getItem(0);
            const std::string restart_rootname_string = restart_rootname_item->getString(0);

            DeckItemPtr restart_report_step_item = restart_dataRecord->getItem(1);
            int restart_report_step_int = restart_report_step_item->getInt(0);

            DeckItemPtr save_item = restart_dataRecord->getItem(2);
            if (save_item->hasValue(0)) {
                throw std::runtime_error("OPM does not support RESTART from a SAVE file, only from RESTART files");
            }

            m_restartInitiated = true;
            m_restartStep = restart_report_step_int;
            m_restartRootName = restart_rootname_string;
        } else if (deck->hasKeyword("RESTART") || deck->hasKeyword("SKIPREST")){
            throw std::runtime_error("Error in deck: Only one of the kewywords RESTART and SKIPREST are supplied. None or both of them should be supplied.");
        }
    }

    bool InitConfig::getRestartInitiated() const {
        return m_restartInitiated;
    }

    int InitConfig::getRestartStep() const {
        return m_restartStep;
    }

    const std::string& InitConfig::getRestartRootName() const {
        return m_restartRootName;
    }
} //namespace Opm
