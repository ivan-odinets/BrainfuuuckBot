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

#include "BrainfuckJobManager.h"

#include "BrainfuckJob.h"

BrainfuckJobManager::BrainfuckJobManager(QObject* parent) :
    QObject{parent}
{}

void BrainfuckJobManager::appendJob(BrainfuckJob* job)
{
    connect(job,&BrainfuckJob::jobFinished,this,&BrainfuckJobManager::_internalJobFinished);
    job->start();
}

void BrainfuckJobManager::_internalJobFinished()
{
    BrainfuckJob* senderJob = qobject_cast<BrainfuckJob*>(sender());
    Q_ASSERT(senderJob != nullptr);

    emit jobFinished(senderJob);
}
