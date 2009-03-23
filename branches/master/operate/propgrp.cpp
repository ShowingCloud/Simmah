/*
 *  A group displaying the properties in the operate notebook.
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
#include <QString>

#include "operate/propgrp.h"

QString PropGrp::propname[PropGrp::PropBottom];
double PropGrp::UpperLimit[PropGrp::PropBottom] = {6, 5.5, 0, 0, 0, 130, 130, 200},
	PropGrp::LowerLimit[PropGrp::PropBottom] = {4, 4.5, 0, 0, 0, 100, 100, 75};
//double PropGrp::UpperLimit[PropGrp::PropBottom] = {0, 5.5, 77, 5.5, 5.5, 137.5, 137.5, 0},
//	PropGrp::LowerLimit[PropGrp::PropBottom] = {0, 4.5, 63, 4.5, 4.5, 112.5, 112.5, 0};
//double PropGrp::UpperLimit[PropGrp::PropBottom] = {15, 15, 100, 15, 15, 500, 500, 1000},
//	PropGrp::LowerLimit[PropGrp::PropBottom] = {0.1, 0.1, 30, 0.1, 0.1, 0, 0, 0};
QString PropGrp::quantity[PropGrp::PropBottom] = {"V", "V", "V", "V", "V", "kHz", "kHz", "mA"};

PropGrp::PropGrp (const QString &name, Properties prop, QWidget *parent)
	: QWidget (parent)
{
	property = prop;

	label = new QLabel (name, this);
	label->setFont (QFont ("Bitstream Sans", 15));
	label->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);

	data = new QLabel (this);
	data->setFont (QFont ("Bitstream Sans", 15));
	data->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);

	error = new QLabel (this);
	error->setFont (QFont ("Bitstream Sans", 12));
	error->setWordWrap (true);

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget (label, 30);
	hbox->addWidget (data, 30);
	hbox->addWidget (error, 40);
	setLayout (hbox);
	setFocusProxy (data);
}

bool PropGrp::RefreshData (const double value)
{
	data->setText (QString ("%1 " + quantity[property]).arg (value));

	if (UpperLimit[property] == 0 && LowerLimit[property] == 0)
		return true;

	if (value > UpperLimit[property]) error->setText (ERR_TOOBIG);
	else if (value < LowerLimit[property]) error->setText (ERR_TOOSMALL);
	else {
		error->setText (ERR_NOERROR);
		return true;
	}
	return false;
}
