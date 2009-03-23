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

#ifndef _OPERATE_H
#define _OPERATE_H	1

#include <QWidget>

#include "operate/loginfo.h"
#include "operate/propgrp.h"
#include "common/loginout.h"
#include "iooper/serialport.h"

class QLabel;
class QVBoxLayout;
class QGroupBox;

class Operate : public QWidget
{
	Q_OBJECT

public:
	Operate (QWidget *parent = 0);

public slots:
	void logedin (QString &num, QString &name, QString &batch);
	void NewData ();
	void ItemsChanged ();
	void GotResult (const int result, const PropGrp::Properties prop);
	void groupclicked (bool checked);

private:
	LogInfo *loginfo;
	LogInOut *loginout;
	QLabel *finallabel;
	QVBoxLayout *operatebox;
	QGroupBox *groupprop;
	PropGrp *prop[PropGrp::PropBottom];
	bool testresult[PropGrp::PropBottom];
};

#endif /* _OPERATE_H */
