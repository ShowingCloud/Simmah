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

	QVBoxLayout *boxitemwp = new QVBoxLayout;
	QLabel *imgl = new QLabel (this);
	QImage img (QString (ITEMS_IMAGE_FILE));
	imgl->setPixmap(QPixmap::fromImage (img.scaledToWidth (1200)));
	boxitemwp->addWidget (imgl);

	QGridLayout *boxitem = new QGridLayout;
	for (i = 0; i < PropGrp::PropBottom; i++) {
		item[i] = new QCheckBox (PropGrp::propname[i]
//				+ QString (":%1").arg (PropGrp::UpperLimit[i]) + " ~ "
//				+ QString ("%1" + PropGrp::quantity[i]).arg (PropGrp::LowerLimit[i])
				, this);
		item[i]->setChecked (true);
		item[i]->setFont (QFont ("Bitstream Sans", 25));
		boxitem->addWidget (item[i], i / 4, i % 4);
		connect (item[i], SIGNAL (stateChanged (int)), this, SLOT (itemchanged ()));
	}
	boxitemwp->addLayout (boxitem);

	groupitem = new QGroupBox (tr ("Check to Enable the Testing Items"), this);
	groupitem->setLayout (boxitemwp);
	groupitem->setVisible (false);

	labelitem = new QLabel (this);
	labelitem->setText (QString (tr ("You don't have the permission to choose the items.")));
	labelitem->setFont (QFont ("Bitstream Sans", 35));
	labelitem->setVisible (true);

	loginout = new LogInOut (true, this);

	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget (groupitem, 95);
	hbox->addWidget (labelitem, 95, Qt::AlignCenter);
	vbox->addLayout (hbox);
	vbox->addWidget (loginout);
	setLayout (vbox);

	setFocusProxy (loginout);

	itemchanged ();
}

void Preferences::itemchanged ()
{
	int i;

	for (i = 0; i < PropGrp::PropBottom; i++)
		itemstate[i] = item[i]->isChecked ();

	emit this->ItemsChanged ();
}

void Preferences::CheckAdministrator (QString &num)
{
	if (num.at(0) == 'X' || num.at(0) == 'x') {
		groupitem->setVisible (true);
		labelitem->setVisible (false);
	} else {
		groupitem->setVisible (false);
		labelitem->setVisible (true);
	}
}
