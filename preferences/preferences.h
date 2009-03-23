/*
 *  The preferences notebook. (header)
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

#ifndef _PREFERENCES_H
#define _PREFERENCES_H	1

#include <QWidget>

#include "operate/propgrp.h"
#include "common/loginout.h"

#define ITEMS_IMAGE_FILE	"data/itemsimage.jpg"

class QComboBox;
class QCheckBox;
class QGroupBox;

class Preferences : public QWidget
{
	Q_OBJECT

public:
	Preferences (QWidget *parent = 0);
	static bool itemstate[PropGrp::PropBottom];

signals:
	void ItemsChanged ();

public slots:
	void itemchanged ();
	void CheckAdministrator (QString &num);

private:
	QCheckBox *item[PropGrp::PropBottom];
	LogInOut *loginout;
	QGroupBox *groupitem;
	QLabel *labelitem;
};

#endif /* _PREFERENCES_H */
