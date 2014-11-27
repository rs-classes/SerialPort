#include "SerialPort.h"

//http://softexpert.wordpress.com/2007/10/18/how-to-connect-to-a-serial-port-in-linux-using-c/

SerialPort::SerialPort(const char* portName, bool debugModues = false)
{
	m_debugModus = debugModues;
	mp_portName = portName;
	
	m_portIsOpen = false;
	
	if(m_debugModus) printf("The serialPort class started in debug modus!");
	
	OpenPort();
}

int SerialPort::OpenPort()
{
	if(m_debugModus) printf("Ser: Opening port");
	
	m_fd1=open(mp_portName, O_RDWR | O_NOCTTY | O_NDELAY);

	if (m_fd1 == -1 )
	{
		if(m_debugModus) printf(“open_port: Unable to open %s – “,mp_portName);
		m_portIsOpen = false;
	}
	else
	{
		fcntl(m_fd1, F_SETFL,0);
		if(m_debugModus) printf(“Port 1 has been sucessfully opened and %d is the file description\n”,m_fd1);
	}
}

char SerialPort::ReadByte()
{
	char byte = NULL;
	int returnVal = -2;
	
	if(m_portIsOpen)
		returnVal=read(fd1,(void*)&byte,1);
	return byte;
}

int SerialPort::ClosePort()
{
	if (m_portIsOpen)
		close(m_fd1);
}


SerialPort::~SerialPort()
{
	ClosePort();
}