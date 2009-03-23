/*
 *  The login notebook. (header)
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

#ifndef _LOGIN_H
#define _LOGIN_H	1

#include <QWidget>

#include "login/trigrp.h"
#include "login/ident.h"
#include "common/loginout.h"

class Login : public QWidget
{
	Q_OBJECT

public:
	Login (QWidget *parent = 0);

public slots:
	void InitHist (TriGrp::Groups grp, QStringList &history);
	void UpdateLoginData (TriGrp::Groups grp, const QString &data);
	void LoggingIn ();

signals:
	void logedin (QString &num, QString &name, QString &batch);
	void switchtab (int index);
	void EnableLogin (bool enable);

private:
	TriGrp *grp[TriGrp::GrpBottom];
	Ident *ident;
	LogInOut *loginout;
	QString logindata[TriGrp::GrpBottom];
	bool dataready[TriGrp::GrpBottom];
};

#endif /* _LOGIN_H */
