/*
 *  The login notebook.
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

#include "login/login.h"
#include "mainwindow.h"

Login::Login (QWidget *parent)
	: QWidget (parent)
{
	grp[TriGrp::GrpNum] = new TriGrp (tr ("Number"), TriGrp::GrpNum, this);
	grp[TriGrp::GrpName] = new TriGrp (tr ("Name"), TriGrp::GrpName, this);
	grp[TriGrp::GrpBatch] = new TriGrp (tr ("Batch"), TriGrp::GrpBatch, this);
	ident = new Ident (this);
	loginout = new LogInOut (false, this);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget (grp[TriGrp::GrpNum]);
	vbox->addWidget (grp[TriGrp::GrpName]);
	vbox->addWidget (grp[TriGrp::GrpBatch]);
	vbox->addWidget (ident);
	vbox->addWidget (loginout);
	setLayout (vbox);

	setFocusProxy (grp[TriGrp::GrpNum]);

	for (int i = 0; i < TriGrp::GrpBottom; i++)
		dataready[i] = false;

	connect (loginout, SIGNAL (logedin ()), this, SLOT (LoggingIn ()));
	connect (this, SIGNAL (EnableLogin (bool)), loginout, SIGNAL (EnableLogin (bool)));
	connect (grp[TriGrp::GrpNum], SIGNAL (PushCombo (TriGrp::Groups, const QString &)),
			this, SLOT (UpdateLoginData (TriGrp::Groups, const QString &)));
	connect (grp[TriGrp::GrpName], SIGNAL (PushCombo (TriGrp::Groups, const QString &)),
			this, SLOT (UpdateLoginData (TriGrp::Groups, const QString &)));
	connect (grp[TriGrp::GrpBatch], SIGNAL (PushCombo (TriGrp::Groups, const QString &)),
			this, SLOT (UpdateLoginData (TriGrp::Groups, const QString &)));
}

void Login::InitHist (TriGrp::Groups ngrp, QStringList &history)
{
	switch (ngrp) {
		case TriGrp::GrpNum:
			emit grp[TriGrp::GrpNum]->InitHist (history);
			break;
		case TriGrp::GrpName:
			emit grp[TriGrp::GrpName]->InitHist (history);
			break;
		case TriGrp::GrpBatch:
			emit grp[TriGrp::GrpBatch]->InitHist (history);
			break;
		default:
			break;
	}
}

void Login::UpdateLoginData (TriGrp::Groups ngrp, const QString &data)
{
	int i;

	if (data != "$pull") {
		logindata[ngrp] = data;
		dataready[ngrp] = true;
	} else {
		dataready[ngrp] = false;
		emit EnableLogin (false);
		return;
	}

	for (i = 0; i < TriGrp::GrpBottom; i++)
		if (!dataready[i]) break;
	if (i == TriGrp::GrpBottom)
		emit EnableLogin (true);
}

void Login::LoggingIn ()
{
	emit logedin (logindata[TriGrp::GrpNum], logindata[TriGrp::GrpName], logindata[TriGrp::GrpBatch]);
	MainWindow::setlogin (true);
	emit switchtab (MainWindow::TabOperate);
}
