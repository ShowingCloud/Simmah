/*
 *  Reading and writing configuration file. (header)
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

#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H	1

#include <QWidget>

#include "login/trigrp.h"

#define CONFIG_FILE_NAME	"data/config"

class QFile;

class ConfigFile : public QWidget
{
	Q_OBJECT

public:
	ConfigFile (QWidget *parent = 0);
	void ReadConfig ();
	~ConfigFile ();

public slots:
	void UpdateConfig (QString &num, QString &name, QString &batch);

signals:
	void HistSignal (TriGrp::Groups grp, QStringList &history);

private:
	QStringList num_hist, name_hist, batch_hist;
	QFile *configfile;
};

#endif /* _CONFIG_FILE_H */
