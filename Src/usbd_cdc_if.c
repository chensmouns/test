/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v2.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */
#include "mixes.h"
#include "stmflash.h"
#include "cmsis_os.h"
#include "radiolink.h"
#include "status.h"
#include "crsf.h"
#include "joystick.h"
#include "stdbool.h"
#include "common.h"
#if defined(LiteRadio_Plus_SX1280)||(LiteRadio_Plus_SX1276)
#include "common.h"
#endif
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t USB_Recive_Buffer[64]; 
extern uint8_t MasterUID[6];
extern uint16_t BuzzerSwitch;
extern bool MasterUidUseChipIDFlag;
/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  /* USER CODE BEGIN 3 */
  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  /* USER CODE BEGIN 5 */
  switch(cmd)
  {
    case CDC_SEND_ENCAPSULATED_COMMAND:

    break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

    break;

    case CDC_SET_COMM_FEATURE:

    break;

    case CDC_GET_COMM_FEATURE:

    break;

    case CDC_CLEAR_COMM_FEATURE:

    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
    case CDC_SET_LINE_CODING:

    break;

    case CDC_GET_LINE_CODING:

    break;

    case CDC_SET_CONTROL_LINE_STATE:

    break;

    case CDC_SEND_BREAK:

    break;

  default:
    break;
  }

  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  /* USER CODE BEGIN 6 */
  char i;
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	for(i=0;i<*Len;i++) 
	{
			USB_Recive_Buffer[i]=Buf[i]; 
	}
	SaveMixValueToFlash();
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
	
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0){
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
void SaveMixValueToFlash(void)
{
    uint16_t writeWord[10];
    for(int i=0;i<8;i++)
    {
        writeWord[i] = (uint16_t)USB_Recive_Buffer[i];
    }
    switch (USB_Recive_Buffer[0])
    {
        case CHANNEILS_INPUT_ID:
        {    
            STMFLASH_Write(CACHE_MIX_CHANNEL_INFO_ADDR+USB_Recive_Buffer[1]*8,&writeWord[2],4);
            mixUpdateFlag = 0x01;
            break;
        }
        case LITE_CONFIGER_INFO_ID:
        {
            uint16_t channelBuff[32];
            STMFLASH_Read(CACHE_MIX_CHANNEL_INFO_ADDR,channelBuff,32);
            STMFLASH_Write(MIX_CHANNEL_INFO_ADDR,channelBuff,32);  
            
            STMFLASH_Write(CONFIGER_INFO_ADDR,&writeWord[1],3); 
            HAL_NVIC_SystemReset();
            break;
        }
        
        case EXTRA_CUSTOM_CONFIG_ID:
        {
            if(USB_Recive_Buffer[1] == 1)
            {
                STMFLASH_Write(BuzzerSwitch_ADDR,&writeWord[2],1); 
                BuzzerSwitch = writeWord[2];
            }
            else if(USB_Recive_Buffer[1] == 2)
            {
                STMFLASH_Write(JoystickDeadZonePercent_ADDR,&writeWord[2],1); 
            }
        }
        
#if defined(LiteRadio_Plus_SX1280)    
        case INTERNAL_CONFIGER_INFO_ID:
        {
            if(writeWord[1] == 0x02)
            {
                internalCRSFdata.crsfParameter.power = writeWord[2];
                internalCRSFdata.crsfParameter.rate = writeWord[3];
                internalCRSFdata.crsfParameter.TLM = writeWord[4];
                tx_config.power = internalCRSFdata.crsfParameter.power;
                tx_config.rate = internalCRSFdata.crsfParameter.rate;
                tx_config.tlm = internalCRSFdata.crsfParameter.TLM;
            }
            break;  
        }
        case UID_BYTES_ID:
        {
            if(USB_Recive_Buffer[1]==0&&USB_Recive_Buffer[2]==0&&USB_Recive_Buffer[3]==0&&USB_Recive_Buffer[4]==0&&USB_Recive_Buffer[5]==0&&USB_Recive_Buffer[6]==0)
            {
                MasterUidUseChipIDFlag = true;
                uint16_t Writetemp[1]; 
                Writetemp[0] = MasterUidUseChipIDFlag;
                STMFLASH_Write(MasterUidUseChipIDFlag_ADDR,Writetemp,1);
            }
            else
            {
                MasterUID[0] = USB_Recive_Buffer[1];
                MasterUID[1] = USB_Recive_Buffer[2];
                MasterUID[2] = USB_Recive_Buffer[3];
                MasterUID[3] = USB_Recive_Buffer[4];
                MasterUID[4] = USB_Recive_Buffer[5];
                MasterUID[5] = USB_Recive_Buffer[6];
                
                MasterUidUseChipIDFlag = false;
                uint16_t Writetemp[1]; 
                Writetemp[0] = MasterUidUseChipIDFlag;
                STMFLASH_Write(MasterUidUseChipIDFlag_ADDR,Writetemp,1);
                STMFLASH_Write(MasterID1FromBindPhrase_ADDR,&writeWord[1],1);
                STMFLASH_Write(MasterID2FromBindPhrase_ADDR,&writeWord[2],1);
                STMFLASH_Write(MasterID3FromBindPhrase_ADDR,&writeWord[3],1);
                STMFLASH_Write(MasterID4FromBindPhrase_ADDR,&writeWord[4],1);
                STMFLASH_Write(MasterID5FromBindPhrase_ADDR,&writeWord[5],1);
                STMFLASH_Write(MasterID6FromBindPhrase_ADDR,&writeWord[6],1);
            }
        }
#endif   
        case EXTERNAL_CONFIGER_INFO_ID:
        {
            if(writeWord[1] == 0x01)
            {
                externalCRSFdata.configStatus = CONFIG_CRSF_ON;
                externalCRSFdata.configUpdateFlag = 0x01;
            }
            else if(writeWord[1] == 0x00)
            {
                externalCRSFdata.configStatus = CONFIG_CRSF_OFF;
            }
            else if(writeWord[1] == 0x02)
            {               
                externalCRSFdata.configSetFlag = 0x01;
                if(writeWord[6] == 0x01)
                {
                    externalCRSFdata.inBindingMode = 0x01;
                }
                else if(writeWord[7] == 0x01)
                {
                    externalCRSFdata.webUpdateMode = 0x01;
                }
                else
                {
                    uint8_t rate = 0,power = 0;
                    power = writeWord[2];
                    rate = writeWord[3];
                    externalCRSFdata.crsfParameter.TLM = writeWord[4];
                    switch (externalCRSFdata.regulatoryDomainIndex)
                    {
                        case NANO_TX_915Mhz:
                            switch(rate)
                            {
                                case 0:
                                    externalCRSFdata.crsfParameter.rate = FREQ_900_RATE_25HZ;
                                    break;
                                case 1:
                                    externalCRSFdata.crsfParameter.rate = FREQ_900_RATE_50HZ;
                                    break;
                                case 2:
                                    externalCRSFdata.crsfParameter.rate = FREQ_900_RATE_100HZ;
                                    break;
                                case 3:
                                    externalCRSFdata.crsfParameter.rate = FREQ_900_RATE_200HZ;
                                    break;
                                default:
                                    break;
                            }
                            
                            break;
                        case NANO_TX_2400Mhz:
                            switch(rate)
                            {
                                case 0:
                                    externalCRSFdata.crsfParameter.rate = FREQ_2400_RATE_50HZ;
                                    break;
                                case 1:
                                    externalCRSFdata.crsfParameter.rate = FREQ_2400_RATE_150HZ;
                                    break;
                                case 2:
                                    externalCRSFdata.crsfParameter.rate = FREQ_2400_RATE_250HZ;
                                    break;
                                case 3:
                                    externalCRSFdata.crsfParameter.rate = FREQ_2400_RATE_500HZ;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                    switch(externalCRSFdata.regulatoryDomainIndex)
                    {
                        case NANO_TX_915Mhz:
                            switch(power)
                            {
                                case power100mw:
                                    externalCRSFdata.crsfParameter.power = power915Mhz100mw;
                                    break;
                                case power250mw:
                                    externalCRSFdata.crsfParameter.power = power915Mhz250mw;
                                    break;
                                case power500mw:
                                    externalCRSFdata.crsfParameter.power = power915Mhz500mw;
                                    break;
                                default:
                                    break;
                            }
                            break;
                            case NANO_TX_2400Mhz:
                                externalCRSFdata.crsfParameter.power = power;
                                break;
                            default:
                                break;
                    }
                    
                }
            }
            break;
        }
        case REQUEST_INFO_ID:
        {
            requestType1 = USB_Recive_Buffer[1];
            requestType2 = USB_Recive_Buffer[2];
            if(requestType1 == 0x00 && requestType2 == 0x01)
            {
                sendSpam = 0;
            }
            if(requestType1 == 0x00 && requestType2 == 0x03)
            {
                configFlag = 1;
            }
            break;
        }
        default:
            break;
    }

}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */
