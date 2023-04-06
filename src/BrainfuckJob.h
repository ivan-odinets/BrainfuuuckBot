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

#ifndef BRAINFUCKJOB_H
#define BRAINFUCKJOB_H

#include <QObject>

#include "QtTelegramBot.h"

class BrainfuckJob : public QObject
{
    Q_OBJECT
public:
    static qint64 tapeSize()                     { return m_tapeSize; }
    static void setTapeSize(qint64 newSize)      { m_tapeSize = newSize; }

    explicit BrainfuckJob(QObject* parent = nullptr);
    ~BrainfuckJob() {}

    void start();

    Telegram::Message   originalMessage() const                                { return m_originalMessage; }
    void                setOriginalMessage(const Telegram::Message& message)   { m_originalMessage = message; }

    QString   brainfuckInput() const                            { return m_inputString; }
    void      setBrainfuckInput(const QString& inputString)     { m_inputString = inputString; }

    QString   outputText() const                                { return m_outputText; }

signals:
    void jobFinished();

private:
    static qint64 m_tapeSize;

    Telegram::Message m_originalMessage;
    QString           m_inputString;
    QString           m_outputText;
};

#endif // BRAINFUCKJOB_H
