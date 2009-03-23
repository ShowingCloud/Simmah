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

#ifndef _IDENT_H
#define _IDENT_H	1

#include <QWidget>

class QLabel;
class QComboBox;

class Ident : public QWidget
{
	Q_OBJECT

public:
	Ident (QWidget *parent = 0);

private:
	QLabel *label;
	QComboBox *combo;
};

#endif /* _IDENT_H */
