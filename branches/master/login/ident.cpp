/*
 *  A group with triple widgets in the login notebook.
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
#include <QComboBox>
#include <QHBoxLayout>

#include "login/ident.h"

Ident::Ident (QWidget *parent)
	: QWidget (parent)
{
	label = new QLabel (tr ("Identification Method"), this);
	label->setFont (QFont ("Bitstream Sans", 28));
	label->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);

	combo = new QComboBox (this);
	combo->setFont (QFont ("Bitstream Sans", 28));
	combo->addItem (tr ("SPC"));
	combo->addItem (tr ("Goalpost"));

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget (label, 20);
	hbox->addWidget (combo, 50);
	hbox->addStretch (30);
	setLayout (hbox);

	setFocusProxy (combo);
}
