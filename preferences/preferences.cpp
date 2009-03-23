/*
 *  The preferences notebook.
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

#include "preferences/preferences.h"

bool Preferences::itemstate[PropGrp::PropBottom];

Preferences::Preferences (QWidget *parent)
	: QWidget (parent)
{
	int i;

	styles = new QComboBox (this);
	styles->addItems (QStyleFactory::keys ());
	QVBoxLayout *boxstyle = new QVBoxLayout;
	boxstyle->addWidget (styles);
	QGroupBox *groupstyle = new QGroupBox (tr ("Select the Window Style"), this);
	groupstyle->setLayout (boxstyle);

	QHBoxLayout *boxitemwp = new QHBoxLayout;
	QVBoxLayout *boxitem = new QVBoxLayout;
	for (i = 0; i < PropGrp::PropBottom; i++) {
		item[i] = new QCheckBox (PropGrp::propname[i]
//				+ QString (":%1").arg (PropGrp::UpperLimit[i]) + " ~ "
//				+ QString ("%1" + PropGrp::quantity[i]).arg (PropGrp::LowerLimit[i])
				, this);
		item[i]->setChecked (true);
		boxitem->addWidget (item[i]);
		connect (item[i], SIGNAL (stateChanged (int)), this, SLOT (itemchanged ()));
	}
	boxitemwp->addLayout (boxitem);

	QLabel *imgl = new QLabel (this);
	QImage img (QString (ITEMS_IMAGE_FILE));
	imgl->setPixmap(QPixmap::fromImage (img.scaledToWidth (600)));
	boxitemwp->addWidget (imgl);

	QGroupBox *groupitem = new QGroupBox (tr ("Check to Enable the Testing Items"), this);
	groupitem->setLayout (boxitemwp);

	loginout = new LogInOut (true, this);

	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget (groupstyle, 10);
	hbox->addWidget (groupitem, 90);
	vbox->addLayout (hbox);
	vbox->addWidget (loginout);
	setLayout (vbox);

	setFocusProxy (loginout);

	connect (styles, SIGNAL (activated (const QString &)), this, SLOT (changestyle (const QString &)));

	itemchanged ();
}

void Preferences::changestyle (const QString &stylename)
{
	QApplication::setStyle (QStyleFactory::create (stylename));
}

void Preferences::itemchanged ()
{
	int i;

	for (i = 0; i < PropGrp::PropBottom; i++)
		itemstate[i] = item[i]->isChecked ();

	emit this->ItemsChanged ();
}
