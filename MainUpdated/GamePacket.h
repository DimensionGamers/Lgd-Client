#ifndef GAME_PACKET_H
#define GAME_PACKET_H

#pragma once

class GamePacket : public ByteBuffer
{
public:
	// just container for later use
	GamePacket() : ByteBuffer(0)
	{
	}

	GamePacket(uint8* packet) : ByteBuffer()
	{
		PSWMSG_HEAD* lpData = (PSWMSG_HEAD*)packet;
		this->append(packet, lpData->get_size());

		this->read_skip<PSWMSG_HEAD>();
	}
};

#endif
