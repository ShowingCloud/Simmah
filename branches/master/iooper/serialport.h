/*
 *  Monitoring the serial port for data. (header)
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

#ifndef _SERIAL_PORT_H
#define _SERIAL_PORT_H	1

#include <QThread>
#include <QQueue>

#include "iooper/serialprotocol.h"

#define SERIAL_PORT_FILE	"/dev/ttyS0"

class QFile;

class SerialPort : public QThread
{
	Q_OBJECT

public:
	SerialPort (QObject *parent = 0);
	~SerialPort ();

	static SerialProtocol GetLastData ()
	{
		return serialdata;
	}

/*	static void EmptyStack ()
	{
		serialstack.clear ();
	}
*/
protected:
	void run ();

signals:
	void GotData ();

public slots:

private:
	QFile *serialport;
	static SerialProtocol serialdata;
};

#endif /* _SERIAL_PORT_H */
