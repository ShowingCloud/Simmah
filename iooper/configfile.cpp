/*
 *  Reading and writing configuration program.
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

#include <QFile>
#include <QTextStream>

#include "iooper/configfile.h"

ConfigFile::ConfigFile (QWidget *parent)
	: QWidget (parent)
{
	int i;
	configfile = new QFile (CONFIG_FILE_NAME);
	if (!configfile->open (QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in (configfile);
	num_hist << in.readLine ();
	if (num_hist.endsWith ("$num_hist")) {
		num_hist.removeLast ();
		i = 0;
		do
			num_hist << in.readLine ();
		while (num_hist.last().at(0) != QChar ('$') && i++ < 10);
	}
	if (num_hist.endsWith ("$name_hist")) {
		num_hist.removeLast ();
		i = 0;
		do
			name_hist << in.readLine ();
		while (name_hist.last().at(0) != QChar ('$') && i++ < 10);
		num_hist << name_hist.takeLast ();
	}
	if (num_hist.endsWith ("$batch_hist")) {
		num_hist.removeLast ();
		i = 0;
		do
			batch_hist << in.readLine ();
		while (batch_hist.last().at(0) != QChar ('$') && i++ < 10);
		num_hist << batch_hist.takeLast ();
	}
	if (num_hist.endsWith ("$end")) {
		num_hist.removeLast ();
		configfile->close ();
		return;
	}
	num_hist.removeLast ();
	configfile->close ();
}

void ConfigFile::ReadConfig ()
{
	emit HistSignal (TriGrp::GrpNum, num_hist);
	emit HistSignal (TriGrp::GrpName, name_hist);
	emit HistSignal (TriGrp::GrpBatch, batch_hist);
}

void ConfigFile::UpdateConfig (QString &num, QString &name, QString &batch)
{
	num_hist.removeAll (num);
	num_hist.prepend (num);
	name_hist.removeAll (name);
	name_hist.prepend (name);
	batch_hist.removeAll (batch);
	batch_hist.prepend (batch);
	ReadConfig ();
}

ConfigFile::~ConfigFile ()
{
	if (!configfile->open (QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out (configfile);
	if (!num_hist.isEmpty ()) {
		out << "$num_hist" << endl;
		do
			out << num_hist.takeFirst () << endl;
		while (!num_hist.isEmpty ());
	}
	if (!name_hist.isEmpty ()) {
		out << "$name_hist" << endl;
		do
			out << name_hist.takeFirst () << endl;
		while (!name_hist.isEmpty ());
	}
	if (!batch_hist.isEmpty ()) {
		out << "$batch_hist" << endl;
		do
			out << batch_hist.takeFirst () << endl;
		while (!batch_hist.isEmpty ());
	}
	out << "$end" << endl;
	configfile->close ();
}
