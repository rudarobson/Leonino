#include "usb.h"
#include "ep0.h"
#include "ep1.h"
#include "ep2.h"
#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#define DESCRIPTOR_DEVICE_LENGTH			0x12
#define DESCRIPTOR_DEVICE_TYPE				0x01
#define VENDOR_ID					0xDEAD
#define PRODUCT_ID					0x0002
#define DEVICE_ID					0x0000

const unsigned char dev_desc[] = {
    DESCRIPTOR_DEVICE_LENGTH,
    DESCRIPTOR_DEVICE_TYPE, //descriptor type
    0x00, //bcd low
    0x02, //bcd high
    0x00, //device class
    0x00, //device subclass
    0x00, //device protocol
    EP0_MAX_PACKET_SIZE, //endpoint 0 max packet size
    LOW_BYTE(VENDOR_ID),
    HIGH_BYTE(VENDOR_ID),
    LOW_BYTE(PRODUCT_ID),
    HIGH_BYTE(PRODUCT_ID),
    LOW_BYTE(DEVICE_ID),
    HIGH_BYTE(DEVICE_ID),
    0x01, //index string of manufacturer
    0x02, //index string of product
    0x00, //index of device's serial number
    0x01 //number of configurations
};

#define DESCRIPTOR_CONFIGURATION_LENGTH			0x09
#define DESCRIPTOR_CONFIGURATION_TYPE			0x02

#define DESCRIPTOR_INTERFACE_TYPE			0x04
#define DESCRIPTOR_INTERFACE_LENGTH		0x09

#define DESCRIPTOR_INTERFACE_INDEX0                     0x00

#define DESCRIPTOR_ENDPOINT_TYPE			0x05
#define DESCRIPTOR_ENDPOINT_LENGTH                      0x07

//#define DESCRIPTOR_CONFIGURATION_TOTAL_LENGTH	(DESCRIPTOR_CONFIGURATION_LENGTH + DESCRIPTOR_INTERFACE_BOOTLOADER_LENGTH + 2* DESCRIPTOR_ENDPOINT_LENGTH + DESCRIPTOR_INTERFACE_APP_LENGTH + 2* DESCRIPTOR_ENDPOINT_LENGTH)
#define DESCRIPTOR_CONFIGURATION_TOTAL_LENGTH	(DESCRIPTOR_CONFIGURATION_LENGTH + DESCRIPTOR_INTERFACE_LENGTH  + 2* DESCRIPTOR_ENDPOINT_LENGTH)
#define DESCRIPTOR_CONFIGURATION_NUM_INTERFACES	0x01



const unsigned char conf_desc_0[] = {
    /* Device Descriptor */
    DESCRIPTOR_CONFIGURATION_LENGTH,
    DESCRIPTOR_CONFIGURATION_TYPE,
    LOW_BYTE(DESCRIPTOR_CONFIGURATION_TOTAL_LENGTH),
    HIGH_BYTE(DESCRIPTOR_CONFIGURATION_TOTAL_LENGTH),
    DESCRIPTOR_CONFIGURATION_NUM_INTERFACES,
    0x01,
    0x00,
    0x80, //D7 must be set
    0x32, //use 100mA

    /* Bootloader Interface Descriptor */
    DESCRIPTOR_INTERFACE_LENGTH, //bLength
    DESCRIPTOR_INTERFACE_TYPE, //bDescriptorType
    DESCRIPTOR_INTERFACE_INDEX0, //interface index
    0x00, //bAlternateSetting
    0x02, //num endpoints
    0xff, //vendor specific class
    0xff, //subclass
    0xff, //protocol - non standard
    0x02, //string describing interface

    /* Endpoint Descriptors */
    /* Enpoint 1 IN Desciptor */
    DESCRIPTOR_ENDPOINT_LENGTH,
    DESCRIPTOR_ENDPOINT_TYPE,
    0x81, //endpoint number 1 IN
    0x02, //Data Endpoint,no synchronization,Bulk
    EP1_MAX_PACKET_SIZE,
    0x00, //High byte
    0x0F, //bInterval

    /* Enpoint 2 OUT Desciptor */
    DESCRIPTOR_ENDPOINT_LENGTH,
    DESCRIPTOR_ENDPOINT_TYPE,
    0x02, //endpoint number 2 OUT
    0x02, //Data Endpoint,no synchronization,Bulk
    EP2_MAX_PACKET_SIZE, //wMaxPacketSize Low byte 64 bytes
    0x00, //High byte
    0x0F, //bInterval
};

#define DESCRIPTOR_STRING_TYPE	0x03

#define DESCRIPTOR_STRING0_LENGTH 0x04
const unsigned char string_desc_0[] = {
    DESCRIPTOR_STRING0_LENGTH,
    DESCRIPTOR_STRING_TYPE,
    0x09,
    0x04
};

//manufacturer
#define DESCRIPTOR_STRING1_LENGTH 0x0C
const unsigned char string_desc_1[] = {
    DESCRIPTOR_STRING1_LENGTH,
    DESCRIPTOR_STRING_TYPE,
    0x00, 'R', 0x00, 'U', 0x00, 'D', 0x00, 'A', 0x00, 0x00
};


//Product
#define DESCRIPTOR_STRING2_LENGTH 0x18
const unsigned char string_desc_2[] = {
    DESCRIPTOR_STRING2_LENGTH,
    DESCRIPTOR_STRING_TYPE,
    'P', 0x00, 0x00, 'R', 0x00, 'O', 0x00, 'G', 0x00, 'R', 0x00, 'A', 0x00, 'M', 0x00, 'M', 0x00, 'E', 0x00, 'R', 0x00, 0x00
};

#endif