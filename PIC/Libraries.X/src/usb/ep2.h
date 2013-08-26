#include "ep1.h"

#ifndef EP2_H
#define	EP2_H

#define EP2_MAX_PACKET_SIZE		0x40
#define EP2_BUFFER_ADDRESS		(EP1_BUFFER_ADDRESS + EP1_MAX_PACKET_SIZE)

void ep2_configure();
void ep2_entry_point(unsigned char ustat);
void ep2_unconfigure();
void ep2_prepare_read();
void ep2_configure_handler(usb_read_handler handler);
#endif	/* EP2_H */

