/*
 **********************************************************************************************************************
 *
 * This file is part of BrainfuuuckBot project
 *
 * Copyright (c) 2023 Ivan Odinets <i_odinets@protonmail.com>
 *
 * BrainfuuuckBot is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version
 * 3 of the License, or (at your option) any later version.
 *
 * BrainfuuuckBot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrainfuuuckBot; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef UI_H
#define UI_H

#include <QString>

class UI
{
public:
    //Commands
    static QString startCmd()               { return m_startCmd; }
    static QString helpCmd()                { return m_helpCmd; }
    static QString chatExecuteCmd()         { return m_chatExecuteCmd; }
    static QString tapeSizeCmd()            { return m_tapeSizeCmd; }

    static QString versionCmd()             { return m_versionCmd; }

    //UI Messages
    static QString startMessage()           { return m_startMessage; }
    static QString helpMessage()            { return m_helpMessage; }
    static QString tapeSizeMessage()        { return m_tapeSizeMessage; }
    static QString unknownCommandMessage()  { return m_unknownCommandmessage; }

    static QString successfullMessage();
    static QString outOfTapeRangeErrorMsg()           { return m_outOfTapeRangeErrorMsg; }
    static QString userInputIsNotSupportedErrorMsg()  { return m_userInputIsNotSupportedErrorMsg; }

private:
    //Commands
    static QString m_startCmd;
    static QString m_helpCmd;
    static QString m_chatExecuteCmd;
    static QString m_tapeSizeCmd;

    static QString m_versionCmd;

    //Messages
    static QString m_startMessage;
    static QString m_helpMessage;
    static QString m_tapeSizeMessage;

    static QString m_unknownCommandmessage;

    static QString m_outOfTapeRangeErrorMsg;
    static QString m_userInputIsNotSupportedErrorMsg;
};

#endif // UI_H
