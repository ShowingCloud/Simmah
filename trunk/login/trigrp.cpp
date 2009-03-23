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

#include "login/trigrp.h"

TriGrp::TriGrp (const QString &name, Groups grp, QWidget *parent)
	: QWidget (parent)
{
	group = grp;

	label = new QLabel (name, this);
	label->setFont (QFont ("Bitstream Sans", 28));
	label->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);

	combo = new QComboBox (this);
	combo->setFont (QFont ("Bitstream Sans", 28));
	combo->setEditable (true);
	combo->setInsertPolicy (QComboBox::InsertAtTop);

	error = new QLabel (this);
	error->setFont (QFont ("Bitstream Sans", 15));
	error->setWordWrap (true);

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget (label, 20);
	hbox->addWidget (combo, 50);
	hbox->addWidget (error, 30);
	setLayout (hbox);
	setFocusProxy (combo);

	connect (combo, SIGNAL (editTextChanged (const QString &)), this, SLOT (Check (const QString &)));
}

void TriGrp::InitHist (QStringList &history)
{
	combo->clear ();
	combo->addItems (history);
	Check (combo->currentText ());
}

void TriGrp::Check (const QString &input)
{
	const QString pull = "$pull";

	if (input == "") {
		error->setText (ERR_EMPTY);
		emit PushCombo (group, pull);
		return;
	}
	switch (group) {
		case GrpNum:
			if (!((input.length() == 3 || input.length() == 4)
						&& (input.at(0) == 'Q' || input.at(0) == 'S' || input.at(0) == 'M' || input.at(0) == 'X' ||
							input.at(0) == 'q' || input.at(0) == 's' || input.at(0) == 'm' || input.at(0) == 'x')
						&& input.at(1) == '-'
						&& input.at(2).isDigit()
						&& (input.length() == 3 || input.at(3).isDigit()))) {
				error->setText (ERR_SYNTAX);
				emit PushCombo (group, pull);
				return;
			}
			error->setText (ERR_CONFIRMED);
			emit PushCombo (group, input);
			return;
		case GrpName:
//			if (!(input.length() == 5 && input.at(0).isLetter() && input.at(1).isLetter() && input.at(2).isLetter()
//						&& input.at(3).isLetter() && input.at(4).isLetter())) {
//				error->setText (ERR_SYNTAX);
//				emit PushCombo (group, pull);
//				return;
//			}
			error->setText (ERR_CONFIRMED);
			emit PushCombo (group, input);
			return;
		case GrpBatch:
//			if (input.length() != 4) {
//				error->setText (ERR_NOBATCH);
//				emit PushCombo (group, pull);
//				return;
//			}
			error->setText (ERR_CONFIRMED);
			emit PushCombo (group, input);
			return;
		default:
			break;
	}
}
