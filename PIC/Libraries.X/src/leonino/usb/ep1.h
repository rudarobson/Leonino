#include "ep0.h"

#ifndef EP1_H
#define	EP1_H

#define EP1_MAX_PACKET_SIZE		USB_MAX_WRITE_SIZE
#define EP1_BUFFER_ADDRESS		(EP0_IN_BUFFER_ADDRESS + EP0_MAX_PACKET_SIZE)

void ep1_configure();
void ep1_unconfigure();
unsigned char ep1_write(unsigned char *buffer, unsigned char count);
unsigned char ep1_send();
void ep1_entry_point(unsigned char ustat);

#endif	/* EP1_H */

