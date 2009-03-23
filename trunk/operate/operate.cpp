/*
 *  The Operate Notebook.
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

#include "operate/operate.h"
#include "iooper/serialprotocol.h"
#include "preferences/preferences.h"

Operate::Operate (QWidget *parent)
	: QWidget (parent)
{
	int i;

	PropGrp::propname[PropGrp::PropPartialV] = QString (tr ("5V Partial Voltage"));
	PropGrp::propname[PropGrp::PropAntennaDriverV] = QString (tr ("Antenna Driver Voltage"));
	PropGrp::propname[PropGrp::PropResonantVpp] = QString (tr ("Resonant Peak Voltage"));
	PropGrp::propname[PropGrp::PropAntennaOutput1] = QString (tr ("Antenna Output 1"));
	PropGrp::propname[PropGrp::PropAntennaOutput2] = QString (tr ("Antenna Output 2"));
	PropGrp::propname[PropGrp::PropAntennaFreq1] = QString (tr ("Antenna Frequency 1"));
	PropGrp::propname[PropGrp::PropAntennaFreq2] = QString (tr ("Antenna Frequency 2"));
	PropGrp::propname[PropGrp::PropWorkingCurrent] = QString (tr ("Working Current"));

	loginfo = new LogInfo (this);

	QGridLayout *finalgrid = new QGridLayout;
	finallabel = new QLabel (this);
	finalgrid->addWidget (finallabel, 0, 0, 8, 4, Qt::AlignCenter);
	totalnumlabel = new QLabel (tr ("Total number in today: "), this);
	finalgrid->addWidget (totalnumlabel, 8, 1);
	totalbadlabel = new QLabel (tr ("Total bad number in today: "), this);
	finalgrid->addWidget (totalbadlabel, 8, 2);
	batchnumlabel = new QLabel (tr ("Total number in this batch: "), this);
	finalgrid->addWidget (batchnumlabel, 9, 1);
	batchbadlabel = new QLabel (tr ("Total bad number in this batch: "), this);
	finalgrid->addWidget (batchbadlabel, 9, 2);

	QVBoxLayout *boxprop = new QVBoxLayout;
	for (i = 0; i < PropGrp::PropBottom; i++) {
		prop[i] = new PropGrp (PropGrp::propname[i], (PropGrp::Properties) i, this);
		boxprop->addWidget (prop[i]);
	}
	groupprop = new QGroupBox (tr ("&Details"), this);
	groupprop->setLayout (boxprop);
	groupprop->setCheckable (true);
	groupprop->setChecked (false);
	connect (groupprop, SIGNAL (clicked (bool)), this, SLOT (groupclicked (bool)));

	loginout = new LogInOut (true, this);

	operatebox = new QVBoxLayout;
	operatebox->addWidget (loginfo, 0);
	operatebox->addLayout (finalgrid, 0);
	operatebox->addWidget (groupprop, 0);
	operatebox->addWidget (loginout, 0);
	setLayout (operatebox);

	setFocusProxy (loginfo);
	groupclicked (false);
	total_num = 0; total_bad = 0;
	batch_num = 0; batch_bad = 0;
}

void Operate::NewData ()
{
	static int i, on_num = 0, off_num = 0, resultnum;
	bool result[PropGrp::PropBottom], s = true;
	static bool bad_token = false;

	SerialProtocol data = SerialPort::GetLastData ();
	qDebug () << data.DeviceID << data.SerialID << data.PartialV << data.AntennaDriverV
		<< data.ResonantVpp << data.AntennaOutput1 << data.AntennaOutput2
		<< data.AntennaFreq1 << data.AntennaFreq2 << data.WorkingCurrent;

	if (!data.SerialID) {
		on_num++;
		resultnum = 0;
		if (on_num == 1) {
			emit loginfo->UpdateLogInfo (NULL, NULL, NULL, data.DeviceID, data.SerialID);
			finallabel->setText ("<font color=green>" + tr ("Waiting for the result...") + "</font>");

			total_num++;
			batch_num++;
			bad_token = true;
			totalnumlabel->setText (QString (tr ("Total number in today: ") + "%1").arg (total_num));
			totalbadlabel->setText (QString (tr ("Total bad number in today: ") + "%1").arg (total_bad));
			batchnumlabel->setText (QString (tr ("Total number in this batch: ") + "%1").arg (batch_num));
			batchbadlabel->setText (QString (tr ("Total bad number in this batch: ") + "%1").arg (batch_bad));
			return;
		}
	} else {
		off_num++;
		if (off_num > 5) {
			on_num = 0;
			off_num = 0;
			finallabel->setText ("<font color=green>" + tr ("Waiting for the result...") + "</font>");
		}
		return ;
	}
	confirmed = false;
	result[PropGrp::PropPartialV] = prop[PropGrp::PropPartialV]->RefreshData ((double) data.PartialV / 65536 * 8.192);
	result[PropGrp::PropAntennaDriverV] = prop[PropGrp::PropAntennaDriverV]->RefreshData ((double) data.AntennaDriverV / 65536 * 8.192);
	result[PropGrp::PropResonantVpp] = prop[PropGrp::PropResonantVpp]->RefreshData ((double) data.ResonantVpp / 65536 * 81.92);
	result[PropGrp::PropAntennaOutput1] = prop[PropGrp::PropAntennaOutput1]->RefreshData ((double) data.AntennaOutput1 / 65536 * 8.192);
	result[PropGrp::PropAntennaOutput2] = prop[PropGrp::PropAntennaOutput2]->RefreshData ((double) data.AntennaOutput2 / 65536 * 8.192);
	result[PropGrp::PropAntennaFreq1] = prop[PropGrp::PropAntennaFreq1]->RefreshData ((double) data.AntennaFreq1 / 100);
	result[PropGrp::PropAntennaFreq2] = prop[PropGrp::PropAntennaFreq2]->RefreshData ((double) data.AntennaFreq2 / 100);
	result[PropGrp::PropWorkingCurrent] = prop[PropGrp::PropWorkingCurrent]->RefreshData ((double) data.WorkingCurrent / 65536 * 819.2);

	off_num = 0;
	for (i = 0; i < PropGrp::PropBottom; i++)
		s &= result[i];
	if (s)
		finallabel->setText ("<font color=blue>" + tr ("Qualified.") + "</font>");
	else if (!result[PropGrp::PropPartialV]) {
		finallabel->setText ("<center><font color=red>" + tr ("Not Qualified.") + "<br>" + tr ("Power managerment chip error") + "</font></center>");
		if (bad_token) {
			total_bad++;
			batch_bad++;
			bad_token = false;
		}
		totalbadlabel->setText (QString (tr ("Total bad number in today: ") + "%1").arg (total_bad));
		batchbadlabel->setText (QString (tr ("Total bad number in this batch: ") + "%1").arg (batch_bad));
	} else if (!result[PropGrp::PropAntennaDriverV]) {
		finallabel->setText ("<center><font color=red>" + tr ("Not Qualified.") + "<br>" + tr ("Driver module error") + "</font></center>");
		if (bad_token) {
			total_bad++;
			batch_bad++;
			bad_token = false;
		}
		totalbadlabel->setText (QString (tr ("Total bad number in today: ") + "%1").arg (total_bad));
		batchbadlabel->setText (QString (tr ("Total bad number in this batch: ") + "%1").arg (batch_bad));
	} else if (!result[PropGrp::PropAntennaFreq1] || !result[PropGrp::PropAntennaFreq2]) {
		finallabel->setText ("<center><font color=red>" + tr ("Not Qualified.") + "<br>" + tr ("No frenquency output for antenna") + "</font></center>");
		if (bad_token) {
			total_bad++;
			batch_bad++;
			bad_token = false;
		}
		totalbadlabel->setText (QString (tr ("Total bad number in today: ") + "%1").arg (total_bad));
		batchbadlabel->setText (QString (tr ("Total bad number in this batch: ") + "%1").arg (batch_bad));
	}
}

void Operate::logedin (QString &num, QString &name, QString &batch)
{
	static QString old_batch (NULL);

	if (batch != old_batch) {
		batch_num = 0;
		batch_bad = 0;
	}
	emit loginfo->UpdateLogInfo (num, name, batch, -1, -1);
}

void Operate::ItemsChanged ()
{
	int i;

	for (i = 0; i < PropGrp::PropBottom; i++)
		if (groupprop->isChecked ())
			prop[i]->setVisible (Preferences::itemstate[i]);
}
/*
void Operate::Detached ()
{
}*/

void Operate::groupclicked (bool checked)
{
	int i;

	if (checked) {
		for (i = 0; i < PropGrp::PropBottom; i++)
			prop[i]->setVisible (Preferences::itemstate[i]);
		loginfo->setFont (QFont ("Bitstream Sans", 18));
		operatebox->setStretch (0, 5);
		finallabel->setFont (QFont ("Bitstream Sans", 18));
		operatebox->setStretch (1, 5);
		groupprop->setFont (QFont ("Bitstream Sans", 18));
		operatebox->setStretch (2, 85);
		operatebox->setStretch (3, 5);
	} else {
		for (i = 0; i < PropGrp::PropBottom; i++)
			prop[i]->setVisible (false);
		loginfo->setFont (QFont ("Bitstream Sans", 25));
		operatebox->setStretch (0, 20);
		finallabel->setFont (QFont ("Bitstream Sans", 80));
		operatebox->setStretch (1, 70);
		groupprop->setFont (QFont ("Bitstream Sans", 18));
		operatebox->setStretch (2, 0);
		operatebox->setStretch (3, 10);
	}
}
