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

#include "BrainfuckJob.h"

#include <QVector>

#include "UI.h"

qint64 BrainfuckJob::m_tapeSize = 30000;

BrainfuckJob::BrainfuckJob(QObject* parent) :
    QObject{parent}
{}

void BrainfuckJob::start()
{
    QVector<quint8> tape(tapeSize(),0);

    int       tapeHead       = 0;
    int       braceCount     = 0;
    int       sourceIndex    = 0;
    QString   output;

    while (sourceIndex < m_inputString.size()) {
        if (tapeHead < 0 || tapeHead > tapeSize()) {
            m_outputText = UI::outOfTapeRangeErrorMsg().arg(tapeHead);
            emit jobFinished();
            return;
        }

        switch (m_inputString[sourceIndex].toLatin1()) {
            case '<':
                --tapeHead;
                break;
            case '>':
                ++tapeHead;
                break;
            case '+':
                ++tape[tapeHead];
                break;
            case '-':
                --tape[tapeHead];
                break;
            case '.':
                output.append(tape[tapeHead]);
                break;
            case ',':
                //TODO: add some support of user input
                m_outputText = UI::userInputIsNotSupportedErrorMsg();
                emit jobFinished();
                return;

            case '[':
                if (tape[tapeHead] == 0) {
                    braceCount++;
                    while (m_inputString[sourceIndex] != ']' || braceCount != 0) {
                        sourceIndex++;
                        if (m_inputString[sourceIndex] == '[')
                            braceCount++;
                        else if (m_inputString[sourceIndex] == ']')
                            braceCount--;
                    }
                }
                break;

            case ']':
                if (tape[tapeHead] != 0) {
                    braceCount++;
                    while (m_inputString[sourceIndex] != '[' || braceCount != 0) {
                        --sourceIndex;
                        if (m_inputString[sourceIndex] == ']') {
                            braceCount++;
                        } else if (m_inputString[sourceIndex] == '[') {
                            braceCount--;
                        }
                    }
                }
                break;
            }
            sourceIndex++;
    }

    m_outputText = UI::successfullMessage().arg(output);

    emit jobFinished();
}
