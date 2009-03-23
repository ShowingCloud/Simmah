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

void PropGrp::RefreshData (const double value)
{
	switch (property) {
		case PropPartialV:
			data->setText (QString ("%1 V").arg (value));
			/* no check */
			error->setText (ERR_NOERROR);
			break;
		case PropAntennaDriverV:
			data->setText (QString ("%1 V").arg (value));
			if (value > 5.5) error->setText (ERR_TOOBIG);
			else if (value < 4.5) error->setText (ERR_TOOSMALL);
			else error->setText (ERR_NOERROR);
			break;
		case PropResonantVpp:
			data->setText (QString ("%1 V").arg (value));
			if (value > 77) error->setText (ERR_TOOBIG);
			else if (value < 63) error->setText (ERR_TOOSMALL);
			else error->setText (ERR_NOERROR);
			break;
		case PropAntennaOutput1:
			data->setText (QString ("%1 V").arg (value));
			if (value > 5.5) error->setText (ERR_TOOBIG);
			else if (value < 4.5) error->setText (ERR_TOOSMALL);
			else error->setText (ERR_NOERROR);
			break;
		case PropAntennaOutput2:
			data->setText (QString ("%1 V").arg (value));
			if (value > 5.5) error->setText (ERR_TOOBIG);
			else if (value < 4.5) error->setText (ERR_TOOSMALL);
			else error->setText (ERR_NOERROR);
			break;
		case PropAntennaFreq1:
			data->setText (QString ("%1 kHz").arg (value));
			if (value > 137.5) error->setText (ERR_TOOBIG);
			else if (value < 112.5) error->setText (ERR_TOOSMALL);
			else error->setText (ERR_NOERROR);
			break;
		case PropAntennaFreq2:
			data->setText (QString ("%1 kHz").arg (value));
			if (value > 137.5) error->setText (ERR_TOOBIG);
			else if (value < 112.5) error->setText (ERR_TOOSMALL);
			else error->setText (ERR_NOERROR);
			break;
		case PropWorkingCurrent:
			data->setText (QString ("%1 mA").arg (value));
			/* no check */
			error->setText (ERR_NOERROR);
			break;
		default:
			break;
	}
}
