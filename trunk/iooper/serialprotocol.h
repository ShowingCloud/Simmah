/*
 *  Serial port communication protocol. (header)
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

#ifndef _SERIAL_PROTOCOL_H
#define _SERIAL_PROTOCOL_H	1

#include <QWidget>

class SerialProtocol
{
public:
	quint8	DeviceID;
	quint8	SerialID;
	quint16	PartialV;
	quint16	AntennaDriverV;
	quint16	ResonantVpp;
	quint16	AntennaOutput1;
	quint16	AntennaOutput2;
	quint16	AntennaFreq1;
	quint16	AntennaFreq2;
	quint16	WorkingCurrent;

	bool valid ()
	{
		return (SerialID == 0);
	}

	friend QDataStream & operator >> (QDataStream &datastream, SerialProtocol &data)
	{
		datastream >> data.DeviceID
			>> data.SerialID
			>> data.WorkingCurrent
			>> data.PartialV
			>> data.AntennaDriverV
			>> data.ResonantVpp
			>> data.AntennaOutput1
			>> data.AntennaOutput2
			>> data.AntennaFreq1
			>> data.AntennaFreq2;
		return datastream;
	}

	friend QDataStream & operator << (QDataStream &datastream, SerialProtocol &data)
	{
		datastream << data.DeviceID
			<< data.SerialID
			<< data.WorkingCurrent
			<< data.PartialV
			<< data.AntennaDriverV
			<< data.ResonantVpp
			<< data.AntennaOutput1
			<< data.AntennaOutput2
			<< data.AntennaFreq1
			<< data.AntennaFreq2;
		return datastream;
	}
};

#endif /* _SERIAL_PROTOCOL_H */
