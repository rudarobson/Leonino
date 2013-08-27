#ifndef USB_H
#define USB_H

#define UCON_USBEN		0x08

#define UCFG_UPUEN		0x10
#define UCFG_FSEN		0x04
#define UCFG_UOEMON             0x40
#define UIER_SOFI		0x40
#define UIER_STALLI		0x20
#define UIER_IDLEI		0x10
#define UIER_TRNI		0x08
#define UIER_ACTVI		0x04
#define UIER_UERRI		0x02
#define UIER_URSTI		0x01

#define UEP_EPHSHK		0x10
#define UEP_EPCONDIS	0x08
#define UEP_EPOUTEN		0x04
#define UEP_EPINEN		0x02
#define UEP_EPSTALL		0x01

#define USTAT_ENDP3			0x40
#define USTAT_ENDP2			0x20
#define USTAT_ENDP1			0x10
#define USTAT_ENDP0			0x08
#define USTAT_DIR			0x04
#define USTAT_ENDPNUM(b)	(((USTAT_ENDP3 | USTAT_ENDP2 | USTAT_ENDP1 | USTAT_ENDP0) & b) >> 3)
#define USTAT_DIRECTION(b)	((b & USTAT_DIR) >> 2)

#define BDSTAT_UOWN		0x80
#define BDSTAT_DTS		0x40
#define BDSTAT_KEN		0x20
#define BDSTAT_INCDIS	0x10
#define BDSTAT_DTSEN	0x08
#define BDSTAT_BSTALL	0x04
#define BDSTAT_BC9		0x02
#define BDSTAT_BC8		0x01
#define BDSTAT_PID3		0x20
#define BDSTAT_PID2		0x10
#define BDSTAT_PID1		0x08
#define BDSTAT_PID0		0x04

#define BDSTAT_PID(b) (((BDSTAT_PID3 | BDSTAT_PID2 | BDSTAT_PID1 | BDSTAT_PID0) & b) >> 2)

#define bmRequestTypeOffset	0x00
#define bRequestOffset		0x01
#define wValueOffset		0x02
#define wIndexOffset		0x04
#define wLengthOffset		0x06

#define bmRequestType_Type(b)				((b[bRequestOffset]>>5) & 0x03)
#define bmRequestType_Recipient(b)			((b[bRequestOffset]) & 0x1f)
#define bmRequestType_Recipient_Device		0x00
#define bmRequestType_Recipient_Interface	0x01
#define bmRequestType_Recipient_Endpoint	0x02

#define bRequest(b)							(b[bRequestOffset])
#define wValue_Low(b)						(b[wValueOffset])
#define wValue_High(b)						(b[wValueOffset + 1])
#define	wIndex(b)							(b[wIndexOffset])
#define wLength(b)							((((unsigned int)(b[wLengthOffset + 1])) << 8) | ((unsigned int) b[wLengthOffset]))

#define bmRequestType_Standard	0x00
#define bmRequestType_Class	0x01
#define bmRequestType_Vendor	0x02



#define PID_OUT				0x01
#define PID_IN				0x09
#define PID_SETUP			0x0D

#define USB_NUM_ENDPOINTS	1
#define HIGH_BYTE(b)		((b >> 8) & 0xff)
#define LOW_BYTE(b)			(b & 0xff)
#define MIN(a,b)			(b < a ? b : a)
#define MAX(a,b)			(b > a ? b : a)
#define BD_ADDRESS_OUT(b)	(0x400 + 8 * b)
#define BD_ADDRESS_IN(b)	(0x400 + 8 * b + 4)

#define TRANS_DIR_IN	1
#define TRANS_DIR_OUT	0

#define USB_MAX_WRITE_SIZE  0x40
#define USB_MAX_READ_SIZE   0x40
typedef void(*usb_handler_t)(void);

typedef struct bdentry {
    unsigned char BDSTAT;
    unsigned char BDCNT;
    unsigned char BDADDRL;
    unsigned char BDADDRH;
} BDENTRY;

typedef  void (*usb_read_handler)();
void usb_device_configure();
void usb_start();
void usb_disable();
void usb_reset();
void usb_handle();
void usb_configure_handler(usb_read_handler);

unsigned char usb_write(unsigned char *buffer, unsigned char count);
unsigned char usb_write_byte(unsigned char byte);
unsigned char usb_read(char *buffer,unsigned char count,unsigned char maxcount);
unsigned char usb_send();
#define DEVICE_CONFIGURED   1
#define DEVICE_ATTACHED     0
char usb_device_state = DEVICE_ATTACHED;

#endif