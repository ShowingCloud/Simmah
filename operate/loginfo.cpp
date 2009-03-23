/*
 *  A group with triple widgets in the login notebook.
 *  Copyright (C) 2009 WANG Guoqin <wangguoqin1001@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

#include "operate/loginfo.h"
#include "login/login.h"

LogInfo::LogInfo (QWidget *parent)
	: QWidget (parent)
{
	this->setFont (QFont ("Bitstream Sans", 12));
	number = new QLabel (this);
	name = new QLabel (this);
	batch = new QLabel (this);
	device = new QLabel (this);
	serial = new QLabel (this);
	time = new QLabel (this);
	sid = 0;

	timer = new QTimer (this);
	connect (timer, SIGNAL (timeout ()), this, SLOT (ShowTime ()));
	timer->start (1000);
	ShowTime ();

	QGridLayout *grid = new QGridLayout (this);
	grid->addWidget (number, 0, 0);
	grid->addWidget (name, 0, 1);
	grid->addWidget (batch, 0, 2);
	grid->addWidget (device, 1, 0);
	grid->addWidget (serial, 1, 1);
	grid->addWidget (time, 1, 2);
	setLayout (grid);

//	setFocusProxy ();
}

void LogInfo::UpdateLogInfo (const QString &s_num, const QString &s_name, const QString &s_batch, const int deviceid, const int serialid)
{
	if (s_num != NULL) number->setText (tr ("Worker No.: ") + s_num);
	if (s_name != NULL) name->setText (tr ("Worker Name: ") + s_name);
	if (s_batch != NULL) batch->setText (tr ("Batch No.: ") + s_batch);
	if (deviceid != -1) device->setText (tr ("Device ID: ") + QString ("%1").arg (deviceid));
	if (serialid != -1) {
		sid++;
		serial->setText (tr ("Serial ID: ") + QString ("%1").arg (sid));
	}
}

void LogInfo::ShowTime ()
{
	time->setText (QDateTime::currentDateTime ().toString (Qt::SystemLocaleLongDate));
}
