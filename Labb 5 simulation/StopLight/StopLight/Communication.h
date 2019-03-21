#pragma once
class Communication {
	private:
		int serial_port;
		
	public:
		Communication();
		void transmit(int);
		int recieve();
};