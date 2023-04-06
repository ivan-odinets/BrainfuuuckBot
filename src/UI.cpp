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

#include "UI.h"

/*
 **********************************************************************************************************************
 * Commands
 */

QString UI::m_startCmd            =    QStringLiteral("/start");
QString UI::m_helpCmd             =    QStringLiteral("/help");
QString UI::m_chatExecuteCmd      =    QStringLiteral("/brainfuck");
QString UI::m_tapeSizeCmd         =    QStringLiteral("/tapeSize");

QString UI::m_versionCmd          =    QStringLiteral("/version");

/*
 **********************************************************************************************************************
 * UI messages
 */

QString UI::m_startMessage        =    QStringLiteral("Send me brainfuck code and I will interpret it. For group chats - "
                                                      "add /brainfuck command before the code itself.");

QString UI::m_helpMessage         =    QStringLiteral("I can interpret brainfuck code. In private messages - jsut send message"
                                                      "containing brainfuck code - and recieve result. In group chats - use "
                                                      "command /brainfuck before your code. Supported commands:\r\n"
                                                      "`- /help             - show this message;\r\n"
                                                      "- /brainfuck <code> - execute <code> (for groups only);\r\n"
                                                      "- /tapeSize         - show currently active tape size;`\r\n\r\n"
                                                      "What the thing is brainfuck - [wiki](https://en.wikipedia.org/wiki/Brainfuck)");

QString UI::m_tapeSizeMessage                    =    QStringLiteral("Current tape size is %1");
QString UI::m_unknownCommandmessage              =    QStringLiteral("Unknown command.");

QString UI::successfullMessage()  { return ((rand() % 2) ? QString("Success! Output:\r\n%1") : QString("*Qapla'!*\r\n%1")); }
QString UI::m_outOfTapeRangeErrorMsg             =    QStringLiteral("Index %1 is out of tape range!");
QString UI::m_userInputIsNotSupportedErrorMsg    =    QStringLiteral("User input is currently not supported!");
