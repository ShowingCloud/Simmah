/*
 *  A group with triple widgets in the login notebook. (header)
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

#ifndef _TRIGRP_H
#define _TRIGRP_H	1

#include <QWidget>

class QLabel;
class QComboBox;

class TriGrp : public QWidget
{
	Q_OBJECT

public:
	enum Groups {
		GrpNum = 0,
		GrpName,
		GrpBatch,
		GrpBottom,
	};
	TriGrp (const QString &name = "", Groups grp = GrpBottom, QWidget *parent = 0);
#define ERR_CONFIRMED	("<font color=blue>" + tr ("No error, please continue.") + "</font>")
#define ERR_SYNTAX		("<font color=red>" + tr ("Syntax error, please check.") + "</font>")
#define ERR_NOBATCH		("<font color=red>" + tr ("No such batch number, please check.") + "</font>")
#define ERR_EMPTY		("<font color=red>" + tr ("Empty, please input.") + "</font>")

public slots:
	void InitHist (QStringList &history);
	void Check (const QString &input);

signals:
	void PushCombo (TriGrp::Groups grp, const QString &data);

private:
	QLabel *label;
	QComboBox *combo;
	QLabel *error;
	Groups group;
};

#endif /* _TRIGRP_H */
