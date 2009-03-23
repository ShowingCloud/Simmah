/*
 *  A group of buttons with login/switchuser and logout,
 *  which is commonly used in all notebooks.
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

#include <QtGui>

#include "common/loginout.h"
#include "mainwindow.h"

LogInOut::LogInOut (bool isSwitchUser, QWidget *parent)
	: QWidget (parent)
{
	if (isSwitchUser)
		this->setFont (QFont ("Bitstream Sans", 15));
	else
		this->setFont (QFont ("Bitstream Sans", 28));

	login = new QPushButton (isSwitchUser ? tr ("Sw&itchUser") : tr ("Log&in"), this);
	logout = new QPushButton (tr ("&Exit"), this);

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addStretch (60);
	hbox->addWidget (login, 20);
	hbox->addWidget (logout, 20);
	setLayout (hbox);

	setFocusProxy (login);

	connect (login, SIGNAL (clicked ()), this, isSwitchUser ? SLOT (switchuser_clicked ()) : SIGNAL (logedin ()));
	connect (logout, SIGNAL (clicked ()), qApp, SLOT (quit ()));
	connect (this, SIGNAL (EnableLogin (bool)), login, SLOT (setEnabled (bool)));
}

void LogInOut::switchuser_clicked ()
{
	MainWindow::setlogin (false);
}
