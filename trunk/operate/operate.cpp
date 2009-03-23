/*
 *  Main program.
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
	for (i = 0; i < PropGrp::PropBottom; i++)
		prop[i] = new PropGrp (PropGrp::propname[i], (PropGrp::Properties) i, this);
	loginout = new LogInOut (true, this);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget (loginfo);
	for (i = 0; i < PropGrp::PropBottom; i++)
		vbox->addWidget (prop[i]);
	vbox->addWidget (loginout);
	setLayout (vbox);

	setFocusProxy (loginfo);
}

void Operate::NewData ()
{
	SerialProtocol data = SerialPort::GetLastData ();
	qDebug () << data.DeviceID << data.SerialID << data.PartialV << data.AntennaDriverV
		<< data.ResonantVpp << data.AntennaOutput1 << data.AntennaOutput2
		<< data.AntennaFreq1 << data.AntennaFreq2 << data.WorkingCurrent;
	emit loginfo->UpdateLogInfo (NULL, NULL, NULL, data.DeviceID, data.SerialID);
	prop[PropGrp::PropPartialV]->RefreshData ((double) data.PartialV / 1024 * 8.192);
	prop[PropGrp::PropAntennaDriverV]->RefreshData ((double) data.AntennaDriverV / 1024 * 8.192);
	prop[PropGrp::PropResonantVpp]->RefreshData ((double) data.ResonantVpp / 1024 * 81.92);
	prop[PropGrp::PropAntennaOutput1]->RefreshData ((double) data.AntennaOutput1 / 1024 * 8.192);
	prop[PropGrp::PropAntennaOutput2]->RefreshData ((double) data.AntennaOutput2 / 1024 * 8.192);
	prop[PropGrp::PropAntennaFreq1]->RefreshData ((double) data.AntennaFreq1 / 100);
	prop[PropGrp::PropAntennaFreq2]->RefreshData ((double) data.AntennaFreq2 / 100);
	prop[PropGrp::PropWorkingCurrent]->RefreshData ((double) data.WorkingCurrent / 1024 * 819.2);
}

void Operate::logedin (QString &num, QString &name, QString &batch)
{
	emit loginfo->UpdateLogInfo (num, name, batch, -1, -1);
}

void Operate::ItemsChanged ()
{
	int i;

	for (i = 0; i < PropGrp::PropBottom; i++)
		prop[i]->setVisible (Preferences::itemstate[i]);
}
