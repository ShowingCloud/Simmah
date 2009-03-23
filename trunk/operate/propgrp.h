/*
 *  A group displaying the properties in the operate notebook. (header)
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

#ifndef _PROPGRP_H
#define _PROPGRP_H	1

#include <QWidget>

class QLabel;
class QString;

class PropGrp : public QWidget
{
	Q_OBJECT

public:
	enum Properties {
		PropPartialV = 0,
		PropAntennaDriverV,
		PropResonantVpp,
		PropAntennaOutput1,
		PropAntennaOutput2,
		PropAntennaFreq1,
		PropAntennaFreq2,
		PropWorkingCurrent,
		PropBottom,
	};

	PropGrp (const QString &name = "", Properties prop = PropBottom, QWidget *parent = 0);
	static QString propname[PropBottom], quantity[PropBottom];
	static double UpperLimit[PropBottom], LowerLimit[PropBottom];
#define ERR_NOERROR		("<font color=blue>" + tr ("The value is in the normal range.") + "</font>")
#define ERR_TOOSMALL		("<font color=red>" + tr ("The value is below the lower limit.") + "</font>")
#define ERR_TOOBIG		("<font color=red>" + tr ("The value is above the upper limit.") + "</font>")

public slots:
	void RefreshData (const double value);

signals:
	void PushResult (const int result, const PropGrp::Properties prop);

private:
	QLabel *label;
	QLabel *data;
	QLabel *error;
	Properties property;
	void HandleResult (const int result);
};

#endif /* _PROPGRP_H */
