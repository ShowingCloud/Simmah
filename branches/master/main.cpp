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

#include "mainwindow.h"

int main (int argc, char **argv)
{
	QApplication app (argc, argv);
//	QApplication::setStyle (QMotifStyle ());

	QString locale = QLocale::system ().name();
	QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));

	QTranslator translator;
	translator.load (QString ("linguist/Feilo_") + locale);
	app.installTranslator (&translator);

	MainWindow window;
	window.setMinimumSize (1250, 950);
	window.show ();
	return app.exec ();
}
