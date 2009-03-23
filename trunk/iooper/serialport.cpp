/*
 *  Monitoring the serial port for data.
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

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <QFile>
#include <QTextStream>
#include <QtGui>

#include "iooper/serialport.h"

SerialProtocol SerialPort::serialdata;

SerialPort::SerialPort (QObject *parent)
	: QThread (parent)
{
	int fd;
	struct termios opt;

	serialport = new QFile (SERIAL_PORT_FILE);
	if (!serialport->open (QIODevice::ReadOnly))
		qApp->quit ();

	fd = serialport->handle ();
	tcgetattr (fd, &opt);
	cfmakeraw (&opt);
	cfsetispeed (&opt, B19200);
	cfsetospeed (&opt, B19200);
	tcsetattr (fd, TCSANOW, &opt);

	this->start ();
}

void SerialPort::run ()
{
	int nread, r, fd = serialport->handle ();
	QDataStream serial (serialport);
//	SerialProtocol data;
	fd_set fdset;
	char tmp[1000];
	struct timeval tv;

	FD_ZERO (&fdset);
	FD_SET (fd, &fdset);

	while (true) {
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		do {
			select (1, &fdset, (fd_set *) NULL, (fd_set *) NULL, &tv);
			ioctl (fd, FIONREAD, &nread);
			if (nread > 18) r = read (fd, tmp, nread - 18);
			else r = 0;
		} while (nread - r != 18);

		serial >> serialdata;
		emit GotData ();
	}
}

SerialPort::~SerialPort ()
{
	this->quit ();
	serialport->close ();
	delete serialport;
}
