/*
 *  Main program.
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

#include "mainwindow.h"

bool MainWindow::loginready = false, MainWindow::administrator = false;
QTabWidget *MainWindow::tab = NULL;

MainWindow::MainWindow ()
{
	tab = new QTabWidget (this);
	setCentralWidget (tab);

	login = new Login (this);
	tab->addTab (login, tr ("&Login"));
	tab->setFont (QFont ("Bitstream Sans", 18));

	operate = new Operate (this);
	tab->addTab (operate, tr ("&Operate"));
	tab->setFont (QFont ("Bitstream Sans", 18));

//	tab->addTab (NULL, tr ("&Details"));

//	tab->addTab (NULL, tr ("&Statistics"));

	preferences = new Preferences (this);
	tab->addTab (preferences, tr ("&Preferences"));
	tab->setFont (QFont ("Bitstream Sans", 18));

	connect (login, SIGNAL (switchtab (int)), tab, SLOT (setCurrentIndex (int)));
	connect (tab, SIGNAL (currentChanged (int)), this, SLOT (TabChanged (int)));

	config = new ConfigFile (this);
	connect (config, SIGNAL (HistSignal (TriGrp::Groups, QStringList &)), login, SLOT (InitHist (TriGrp::Groups, QStringList &)));
	config->ReadConfig ();

	serial = new SerialPort ();
	connect (serial, SIGNAL (GotData ()), operate, SLOT (NewData ()));

	connect (login, SIGNAL (logedin (QString &, QString &, QString &)), operate, SLOT (logedin (QString &, QString &, QString &)));
	connect (login, SIGNAL (logedin (QString &, QString &, QString &)), config, SLOT (UpdateConfig (QString &, QString &, QString &)));
	connect (login, SIGNAL (logedin (QString &, QString &, QString &)), preferences, SLOT (CheckAdministrator (QString &)));
	connect (preferences, SIGNAL (ItemsChanged ()), operate, SLOT (ItemsChanged ()));
}

MainWindow::~MainWindow ()
{
	delete config;
	delete operate;
	delete login;
	delete tab;
}

void MainWindow::TabChanged (int index)
{
	QMessageBox msgBox;

	switch (index) {
		case TabLogin:
			setlogin (false);
//			msgBox.setText (tr ("You have logged out."));
//			msgBox.setFont (QFont ("Bitstream Sans", 18));
//			msgBox.exec ();
			break;
//		case TabPreferences:
//			if (!administrator) {
//				tab->setCurrentIndex (TabOperate);
//				msgBox.setText (tr ("You don't have this premission."));
//				msgBox.setFont (QFont ("Bitstream Sans", 18));
//				msgBox.exec ();
//			}
//			break;
		default:
			if (!loginready) {
				tab->setCurrentIndex (TabLogin);
//				msgBox.setText (tr ("You have not yet logged in."));
//				msgBox.setFont (QFont ("Bitstream Sans", 18));
//				msgBox.exec ();
			}
			break;
	}
}

void MainWindow::setlogin (bool logedin)
{
	loginready = logedin;

	if (!logedin) {
		tab->setCurrentIndex (TabLogin);
		administrator = false;
	}
}
