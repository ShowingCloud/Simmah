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

#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H	1

#include <QMainWindow>
#include "login/login.h"
#include "operate/operate.h"
#include "preferences/preferences.h"
#include "iooper/configfile.h"
#include "iooper/serialport.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	enum Tabs {
		TabLogin = 0,
		TabOperate,
//		TabDetails,
//		TabStatistics,
		TabPreferences,
		TabBottom,
	};
	MainWindow ();
	~MainWindow ();
	static void setlogin (bool logedin);

public slots:
	static void TabChanged (int index);
	void CheckAdministrator (QString &num, QString &name, QString &batch);

private:
	static QTabWidget *tab;
	Login *login;
	Operate *operate;
	Preferences *preferences;
	ConfigFile *config;
	SerialPort *serial;
	static bool loginready, administrator;
};

#endif /* _MAIN_WINDOW_H */
