/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Following MISRA-C rules are deviated in the below code block */
/* MISRA C-2012 Rule 11.1 */
/* MISRA C-2012 Rule 11.3 */
/* MISRA C-2012 Rule 11.8 */
/* Forward declaration of PHY initialization data */
const DRV_ETHPHY_INIT tcpipPhyInitData_KSZ8091;

/* Forward declaration of GMAC initialization data */
const TCPIP_MODULE_MAC_PIC32C_CONFIG tcpipGMACInitData;


/* Forward declaration of MIIM 0 initialization data */
static const DRV_MIIM_INIT drvMiimInitData_0;

// <editor-fold defaultstate="collapsed" desc="DRV_SDMMC Instance 0 Initialization Data">

/* SDMMC Client Objects Pool */
static DRV_SDMMC_CLIENT_OBJ drvSDMMC0ClientObjPool[DRV_SDMMC_IDX0_CLIENTS_NUMBER];

/* SDMMC Transfer Objects Pool */
static DRV_SDMMC_BUFFER_OBJ drvSDMMC0BufferObjPool[DRV_SDMMC_IDX0_QUEUE_SIZE];

static const DRV_SDMMC_PLIB_API drvSDMMC0PlibAPI = {
    .sdhostCallbackRegister = (DRV_SDMMC_PLIB_CALLBACK_REGISTER)SDHC1_CallbackRegister,
    .sdhostInitModule = (DRV_SDMMC_PLIB_INIT_MODULE)SDHC1_ModuleInit,
    .sdhostSetClock  = (DRV_SDMMC_PLIB_SET_CLOCK)SDHC1_ClockSet,
    .sdhostIsCmdLineBusy = (DRV_SDMMC_PLIB_IS_CMD_LINE_BUSY)SDHC1_IsCmdLineBusy,
    .sdhostIsDatLineBusy = (DRV_SDMMC_PLIB_IS_DATA_LINE_BUSY)SDHC1_IsDatLineBusy,
    .sdhostSendCommand = (DRV_SDMMC_PLIB_SEND_COMMAND)SDHC1_CommandSend,
    .sdhostReadResponse = (DRV_SDMMC_PLIB_READ_RESPONSE)SDHC1_ResponseRead,
    .sdhostSetBlockCount = (DRV_SDMMC_PLIB_SET_BLOCK_COUNT)SDHC1_BlockCountSet,
    .sdhostSetBlockSize = (DRV_SDMMC_PLIB_SET_BLOCK_SIZE)SDHC1_BlockSizeSet,
    .sdhostSetBusWidth = (DRV_SDMMC_PLIB_SET_BUS_WIDTH)SDHC1_BusWidthSet,
    .sdhostSetSpeedMode = (DRV_SDMMC_PLIB_SET_SPEED_MODE)SDHC1_SpeedModeSet,
    .sdhostSetupDma = (DRV_SDMMC_PLIB_SETUP_DMA)SDHC1_DmaSetup,
    .sdhostGetCommandError = (DRV_SDMMC_PLIB_GET_COMMAND_ERROR)SDHC1_CommandErrorGet,
    .sdhostGetDataError = (DRV_SDMMC_PLIB_GET_DATA_ERROR)SDHC1_DataErrorGet,
    .sdhostClockEnable = (DRV_SDMMC_PLIB_CLOCK_ENABLE)SDHC1_ClockEnable,
    .sdhostResetError = (DRV_SDMMC_PLIB_RESET_ERROR)SDHC1_ErrorReset,
    .sdhostIsCardAttached = (DRV_SDMMC_PLIB_IS_CARD_ATTACHED)SDHC1_IsCardAttached,
    .sdhostIsWriteProtected = (DRV_SDMMC_PLIB_IS_WRITE_PROTECTED)NULL,
};

/*** SDMMC Driver Initialization Data ***/
static const DRV_SDMMC_INIT drvSDMMC0InitData =
{
    .sdmmcPlib                      = &drvSDMMC0PlibAPI,
    .bufferObjPool                  = (uintptr_t)&drvSDMMC0BufferObjPool[0],
    .bufferObjPoolSize              = DRV_SDMMC_IDX0_QUEUE_SIZE,
    .clientObjPool                  = (uintptr_t)&drvSDMMC0ClientObjPool[0],
    .numClients                     = DRV_SDMMC_IDX0_CLIENTS_NUMBER,
    .protocol                       = DRV_SDMMC_IDX0_PROTOCOL_SUPPORT,
    .cardDetectionMethod            = DRV_SDMMC_IDX0_CARD_DETECTION_METHOD,
    .cardDetectionPollingIntervalMs = 0,
    .isWriteProtectCheckEnabled     = false,
    .speedMode                      = DRV_SDMMC_IDX0_CONFIG_SPEED_MODE,
    .busWidth                       = DRV_SDMMC_IDX0_CONFIG_BUS_WIDTH,
	.sleepWhenIdle 					= false,
    .isFsEnabled                    = true,
};
// </editor-fold>




// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
/*** KSZ8091 PHY Driver Time-Out Initialization Data ***/
DRV_ETHPHY_TMO drvksz8091Tmo = 
{
    .resetTmo = DRV_ETHPHY_KSZ8091_RESET_CLR_TMO,
    .aNegDoneTmo = DRV_ETHPHY_KSZ8091_NEG_DONE_TMO,
    .aNegInitTmo = DRV_ETHPHY_KSZ8091_NEG_INIT_TMO,    
};

/*** ETH PHY Initialization Data ***/
const DRV_ETHPHY_INIT tcpipPhyInitData_KSZ8091 =
{    
    .ethphyId               = DRV_KSZ8091_PHY_PERIPHERAL_ID,
    .phyAddress             = DRV_KSZ8091_PHY_ADDRESS,
    .phyFlags               = DRV_KSZ8091_PHY_CONFIG_FLAGS,
    .pPhyObject             = &DRV_ETHPHY_OBJECT_KSZ8091,
    .ethphyTmo              = &drvksz8091Tmo,
    .pMiimObject            = &DRV_MIIM_OBJECT_BASE_Default,
    .pMiimInit              = &drvMiimInitData_0,
    .miimIndex              = 0,


    .resetFunction          = 0,
};



// <editor-fold defaultstate="collapsed" desc="TCP/IP Stack Initialization Data">
// *****************************************************************************
// *****************************************************************************
// Section: TCPIP Data
// *****************************************************************************
// *****************************************************************************
/*** ARP Service Initialization Data ***/
const TCPIP_ARP_MODULE_CONFIG tcpipARPInitData =
{ 
    .cacheEntries       = TCPIP_ARP_CACHE_ENTRIES,     
    .deleteOld          = TCPIP_ARP_CACHE_DELETE_OLD,    
    .entrySolvedTmo     = TCPIP_ARP_CACHE_SOLVED_ENTRY_TMO, 
    .entryPendingTmo    = TCPIP_ARP_CACHE_PENDING_ENTRY_TMO, 
    .entryRetryTmo      = TCPIP_ARP_CACHE_PENDING_RETRY_TMO, 
    .permQuota          = TCPIP_ARP_CACHE_PERMANENT_QUOTA, 
    .purgeThres         = TCPIP_ARP_CACHE_PURGE_THRESHOLD, 
    .purgeQuanta        = TCPIP_ARP_CACHE_PURGE_QUANTA, 
    .retries            = TCPIP_ARP_CACHE_ENTRY_RETRIES, 
    .gratProbeCount     = TCPIP_ARP_GRATUITOUS_PROBE_COUNT,
};


/*** UDP Sockets Initialization Data ***/
const TCPIP_UDP_MODULE_CONFIG tcpipUDPInitData =
{
    .nSockets       = TCPIP_UDP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_UDP_SOCKET_DEFAULT_TX_SIZE, 
};

/*** TCP Sockets Initialization Data ***/
const TCPIP_TCP_MODULE_CONFIG tcpipTCPInitData =
{
    .nSockets       = TCPIP_TCP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_TX_SIZE, 
    .sktRxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_RX_SIZE,
};



/*** SNTP Client Initialization Data ***/
const TCPIP_SNTP_MODULE_CONFIG tcpipSNTPInitData =
{
    .ntp_server             = TCPIP_NTP_SERVER,
    .ntp_interface          = TCPIP_NTP_DEFAULT_IF,
    .ntp_connection_type    = TCPIP_NTP_DEFAULT_CONNECTION_TYPE,
    .ntp_reply_timeout      = TCPIP_NTP_REPLY_TIMEOUT,
    .ntp_stamp_timeout      = TCPIP_NTP_TIME_STAMP_TMO,
    .ntp_success_interval   = TCPIP_NTP_QUERY_INTERVAL,
    .ntp_error_interval     = TCPIP_NTP_FAST_QUERY_INTERVAL,
};



/*** DHCP client Initialization Data ***/
const TCPIP_DHCP_MODULE_CONFIG tcpipDHCPInitData =
{     
    .dhcpEnable     = false,   
    .dhcpTmo        = TCPIP_DHCP_TIMEOUT,
    .dhcpCliPort    = TCPIP_DHCP_CLIENT_CONNECT_PORT,
    .dhcpSrvPort    = TCPIP_DHCP_SERVER_LISTEN_PORT,

};


/*** ICMP Server Initialization Data ***/
const TCPIP_ICMP_MODULE_CONFIG tcpipICMPInitData = 
{
    0
};












/*** DNS Client Initialization Data ***/
const TCPIP_DNS_CLIENT_MODULE_CONFIG tcpipDNSClientInitData =
{
    .deleteOldLease         = TCPIP_DNS_CLIENT_DELETE_OLD_ENTRIES,
    .cacheEntries           = TCPIP_DNS_CLIENT_CACHE_ENTRIES,
    .entrySolvedTmo         = TCPIP_DNS_CLIENT_CACHE_ENTRY_TMO,    
    .nIPv4Entries  = TCPIP_DNS_CLIENT_CACHE_PER_IPV4_ADDRESS,
    .ipAddressType       = TCPIP_DNS_CLIENT_ADDRESS_TYPE,
    .nIPv6Entries  = TCPIP_DNS_CLIENT_CACHE_PER_IPV6_ADDRESS,
};



/*** IPv4 Initialization Data ***/


const TCPIP_IPV4_MODULE_CONFIG  tcpipIPv4InitData = 
{
    .arpEntries = TCPIP_IPV4_ARP_SLOTS, 
};






TCPIP_STACK_HEAP_INTERNAL_CONFIG tcpipHeapConfig =
{
    .heapType = TCPIP_STACK_HEAP_TYPE_INTERNAL_HEAP,
    .heapFlags = TCPIP_STACK_HEAP_USE_FLAGS,
    .heapUsage = TCPIP_STACK_HEAP_USAGE_CONFIG,
    .malloc_fnc = TCPIP_STACK_MALLOC_FUNC,
    .free_fnc = TCPIP_STACK_FREE_FUNC,
    .heapSize = TCPIP_STACK_DRAM_SIZE,
};


const TCPIP_NETWORK_CONFIG __attribute__((unused))  TCPIP_HOSTS_CONFIGURATION[] =
{
    /*** Network Configuration Index 0 ***/
    {
        .interface = TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX0,
        .hostName = TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX0,
        .macAddr = TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX0,
        .ipAddr = TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX0,
        .ipMask = TCPIP_NETWORK_DEFAULT_IP_MASK_IDX0,
        .gateway = TCPIP_NETWORK_DEFAULT_GATEWAY_IDX0,
        .priDNS = TCPIP_NETWORK_DEFAULT_DNS_IDX0,
        .secondDNS = TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX0,
        .powerMode = TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX0,
        .startFlags = TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX0,
        .pMacObject = &TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX0,
    },
};

const size_t TCPIP_HOSTS_CONFIGURATION_SIZE = sizeof (TCPIP_HOSTS_CONFIGURATION) / sizeof (*TCPIP_HOSTS_CONFIGURATION);

const TCPIP_STACK_MODULE_CONFIG TCPIP_STACK_MODULE_CONFIG_TBL [] =
{
    {TCPIP_MODULE_IPV4,             &tcpipIPv4InitData},

    {TCPIP_MODULE_ICMP,             0},                             // TCPIP_MODULE_ICMP

    {TCPIP_MODULE_ARP,              &tcpipARPInitData},             // TCPIP_MODULE_ARP
    {TCPIP_MODULE_UDP,              &tcpipUDPInitData},             // TCPIP_MODULE_UDP
    {TCPIP_MODULE_TCP,              &tcpipTCPInitData},             // TCPIP_MODULE_TCP
    {TCPIP_MODULE_DHCP_CLIENT,      &tcpipDHCPInitData},            // TCPIP_MODULE_DHCP_CLIENT
    {TCPIP_MODULE_DNS_CLIENT,       &tcpipDNSClientInitData},       // TCPIP_MODULE_DNS_CLIENT
    {TCPIP_MODULE_SNTP,             &tcpipSNTPInitData},            // TCPIP_MODULE_SNTP

    {TCPIP_MODULE_COMMAND,          0},                             // TCPIP_MODULE_COMMAND,
    { TCPIP_MODULE_MANAGER,         &tcpipHeapConfig },             // TCPIP_MODULE_MANAGER

// MAC modules
    {TCPIP_MODULE_MAC_PIC32C,       &tcpipGMACInitData},            // TCPIP_MODULE_MAC_PIC32C

};

const size_t TCPIP_STACK_MODULE_CONFIG_TBL_SIZE = sizeof (TCPIP_STACK_MODULE_CONFIG_TBL) / sizeof (*TCPIP_STACK_MODULE_CONFIG_TBL);
/*********************************************************************
 * Function:        SYS_MODULE_OBJ TCPIP_STACK_Init()
 *
 * PreCondition:    None
 *
 * Input:
 *
 * Output:          valid system module object if Stack and its componets are initialized
 *                  SYS_MODULE_OBJ_INVALID otherwise
 *
 * Overview:        The function starts the initialization of the stack.
 *                  If an error occurs, the SYS_ERROR() is called
 *                  and the function de-initialize itself and will return false.
 *
 * Side Effects:    None
 *
 * Note:            This function must be called before any of the
 *                  stack or its component routines are used.
 *
 ********************************************************************/


SYS_MODULE_OBJ TCPIP_STACK_Init(void)
{
    TCPIP_STACK_INIT    tcpipInit;

    tcpipInit.pNetConf = TCPIP_HOSTS_CONFIGURATION;
    tcpipInit.nNets = TCPIP_HOSTS_CONFIGURATION_SIZE;
    tcpipInit.pModConfig = TCPIP_STACK_MODULE_CONFIG_TBL;
    tcpipInit.nModules = TCPIP_STACK_MODULE_CONFIG_TBL_SIZE;
    tcpipInit.initCback = 0;

    return TCPIP_STACK_Initialize(0, &tcpipInit.moduleInit);
}
// </editor-fold>


uint8_t txPrioNumToQueIndxGmac [DRV_GMAC_NUMBER_OF_QUEUES];
uint8_t rxPrioNumToQueIndxGmac [DRV_GMAC_NUMBER_OF_QUEUES];

/*** GMAC Initialization Data ***/
TCPIP_MODULE_GMAC_QUEUE_CONFIG  gmac_queue_config[DRV_GMAC_NUMBER_OF_QUEUES]=
{
   {   /** QUEUE 0 Initialization**/
       .queueTxEnable = true,
       .queueRxEnable = true,
       .nRxDescCnt    = 8,
       .nTxDescCnt    = 8,
       .rxBufferSize  = 1536,
       .txMaxPktSize  = 1536,
       .nRxDedicatedBuffers   = 8,
       .nRxAddlBuffCount  = 2,
       .nRxBuffCntThres   = 1,
       .nRxBuffAllocCnt   = 2,   
       .queueIntSrc       = GMAC_IRQn,                               
   },
};

const TCPIP_MODULE_MAC_PIC32C_CONFIG tcpipGMACInitData =
{ 
       .gmac_queue_config = gmac_queue_config,
       .macQueNum = DRV_GMAC_NUMBER_OF_QUEUES, 
       .txPrioNumToQueIndx = txPrioNumToQueIndxGmac,
       .rxPrioNumToQueIndx = rxPrioNumToQueIndxGmac,
       .ethFlags               = TCPIP_GMAC_ETH_OPEN_FLAGS,    
       .linkInitDelay          = DRV_KSZ8091_PHY_LINK_INIT_DELAY,
       .ethModuleId            = TCPIP_GMAC_MODULE_ID,
       .pPhyBase               = &DRV_ETHPHY_OBJECT_BASE_Default,
       .pPhyInit               = &tcpipPhyInitData_KSZ8091,
       .checksumOffloadRx      = DRV_GMAC_RX_CHKSM_OFFLOAD,
       .checksumOffloadTx      = DRV_GMAC_TX_CHKSM_OFFLOAD,
       .macTxPrioNum           = TCPIP_GMAC_TX_PRIO_COUNT,
       .macRxPrioNum           = TCPIP_GMAC_RX_PRIO_COUNT,  
       .macRxFilt              = TCPIP_GMAC_RX_FILTERS,
};


/*** MIIM Driver Instance 0 Configuration ***/
static const DRV_MIIM_INIT drvMiimInitData_0 =
{
   .miimId = DRV_MIIM_ETH_MODULE_ID_0,
};

/* Net Presentation Layer Data Definitions */
#include "net_pres/pres/net_pres_enc_glue.h"

static const NET_PRES_TransportObject netPresTransObject0SS = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_TCP_ServerOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_TCP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_TCP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_TCP_IsConnected,
    .fpWasReset          = (NET_PRES_TransBool)TCPIP_TCP_WasReset,
    .fpWasDisconnected   = (NET_PRES_TransBool)TCPIP_TCP_WasDisconnected,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_TCP_Disconnect,
    .fpConnect           = (NET_PRES_TransBool)TCPIP_TCP_Connect,
    .fpClose             = (NET_PRES_TransClose)TCPIP_TCP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_TCP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_TCP_Flush,
    .fpPeek              = (NET_PRES_TransPeek)TCPIP_TCP_ArrayPeek,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_TCP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_TCP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_TCP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_TCP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_TCP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_TCP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_TCP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_TCPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0SC = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_TCP_ClientOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_TCP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_TCP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_TCP_IsConnected,
    .fpWasReset          = (NET_PRES_TransBool)TCPIP_TCP_WasReset,
    .fpWasDisconnected   = (NET_PRES_TransBool)TCPIP_TCP_WasDisconnected,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_TCP_Disconnect,
    .fpConnect           = (NET_PRES_TransBool)TCPIP_TCP_Connect,
    .fpClose             = (NET_PRES_TransClose)TCPIP_TCP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_TCP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_TCP_Flush,
    .fpPeek              = (NET_PRES_TransPeek)TCPIP_TCP_ArrayPeek,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_TCP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_TCP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_TCP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_TCP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_TCP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_TCP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_TCP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_TCPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0DS = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_UDP_ServerOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_UDP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_UDP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_UDP_IsConnected,
    .fpWasReset          = NULL,
    .fpWasDisconnected   = NULL,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_UDP_Disconnect,
    .fpConnect          = NULL,
    .fpClose             = (NET_PRES_TransClose)TCPIP_UDP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_UDP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_UDP_Flush,
    .fpPeek              = NULL,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_UDP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_UDP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_UDP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_UDP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_UDP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_UDP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_UDP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_UDPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0DC = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_UDP_ClientOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_UDP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_UDP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_UDP_IsConnected,
    .fpWasReset          = NULL,
    .fpWasDisconnected   = NULL,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_UDP_Disconnect,
    .fpConnect          = NULL,
    .fpClose             = (NET_PRES_TransClose)TCPIP_UDP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_UDP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_UDP_Flush,
    .fpPeek              = NULL,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_UDP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_UDP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_UDP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_UDP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_UDP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_UDP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_UDP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_UDPSecurePortGet,
};

static const NET_PRES_INST_DATA netPresCfgs[] = 
{  
        
    {
        .pTransObject_ss = &netPresTransObject0SS,
        .pTransObject_sc = &netPresTransObject0SC,
        .pTransObject_ds = &netPresTransObject0DS,
        .pTransObject_dc = &netPresTransObject0DC,
        .pProvObject_ss = NULL,
        .pProvObject_sc = &net_pres_EncProviderStreamClient0,
        .pProvObject_ds = NULL,
        .pProvObject_dc = NULL,
    },
        
};

static const NET_PRES_INIT_DATA netPresInitData = 
{
    .numLayers = sizeof(netPresCfgs) / sizeof(NET_PRES_INST_DATA),
    .pInitData = netPresCfgs
};
  
 

// <editor-fold defaultstate="collapsed" desc="File System Initialization Data">

 const SYS_FS_MEDIA_MOUNT_DATA sysfsMountTable[SYS_FS_VOLUME_NUMBER] =
{
    {
        .mountName = SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0,
        .devName   = SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0,
        .mediaType = SYS_FS_MEDIA_TYPE_IDX0,
        .fsType   = SYS_FS_TYPE_IDX0
    },
};


static const SYS_FS_FUNCTIONS FatFsFunctions =
{
    .mount             = FATFS_mount,
    .unmount           = FATFS_unmount,
    .open              = FATFS_open,
    .read_t              = FATFS_read,
    .close             = FATFS_close,
    .seek              = FATFS_lseek,
    .fstat             = FATFS_stat,
    .getlabel          = FATFS_getlabel,
    .currWD            = FATFS_getcwd,
    .getstrn           = FATFS_gets,
    .openDir           = FATFS_opendir,
    .readDir           = FATFS_readdir,
    .closeDir          = FATFS_closedir,
    .chdir             = FATFS_chdir,
    .chdrive           = FATFS_chdrive,
    .write_t             = FATFS_write,
    .tell              = FATFS_tell,
    .eof               = FATFS_eof,
    .size              = FATFS_size,
    .mkdir             = FATFS_mkdir,
    .remove_t            = FATFS_unlink,
    .setlabel          = FATFS_setlabel,
    .truncate          = FATFS_truncate,
    .chmode            = FATFS_chmod,
    .chtime            = FATFS_utime,
    .rename_t            = FATFS_rename,
    .sync              = FATFS_sync,
    .putchr            = FATFS_putc,
    .putstrn           = FATFS_puts,
    .formattedprint    = FATFS_printf,
    .testerror         = FATFS_error,
    .formatDisk        = (FORMAT_DISK)FATFS_mkfs,
    .partitionDisk     = FATFS_fdisk,
    .getCluster        = FATFS_getclusters
};




static const SYS_FS_REGISTRATION_TABLE sysFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = FAT,
        .nativeFileSystemFunctions = &FatFsFunctions
    }
};
// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

static const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)SYSTICK_TimerCallbackSet,
    .timerStart = (SYS_TIME_PLIB_START)SYSTICK_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)SYSTICK_TimerStop,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)SYSTICK_TimerFrequencyGet,
    .timerInterruptRestore = (SYS_TIME_PLIB_INTERRUPT_RESTORE)SYSTICK_TimerInterruptRestore,
    .timerInterruptDisable = (SYS_TIME_PLIB_INTERRUPT_DISABLE)SYSTICK_TimerInterruptDisable,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)SYSTICK_TimerPeriodSet,
};

static const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = SysTick_IRQn,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 0 Initialization Data">


static const SYS_CONSOLE_UART_PLIB_INTERFACE sysConsole0UARTPlibAPI =
{
    .read_t = (SYS_CONSOLE_UART_PLIB_READ)SERCOM5_USART_Read,
    .readCountGet = (SYS_CONSOLE_UART_PLIB_READ_COUNT_GET)SERCOM5_USART_ReadCountGet,
    .readFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_READ_FREE_BUFFFER_COUNT_GET)SERCOM5_USART_ReadFreeBufferCountGet,
    .write_t = (SYS_CONSOLE_UART_PLIB_WRITE)SERCOM5_USART_Write,
    .writeCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_COUNT_GET)SERCOM5_USART_WriteCountGet,
    .writeFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_FREE_BUFFER_COUNT_GET)SERCOM5_USART_WriteFreeBufferCountGet,
};

static const SYS_CONSOLE_UART_INIT_DATA sysConsole0UARTInitData =
{
    .uartPLIB = &sysConsole0UARTPlibAPI,
};

static const SYS_CONSOLE_INIT sysConsole0Init =
{
    .deviceInitData = (const void*)&sysConsole0UARTInitData,
    .consDevDesc = &sysConsoleUARTDevDesc,
    .deviceIndex = 0,
};



// </editor-fold>


const SYS_CMD_INIT sysCmdInit =
{
    .moduleInit = {0},
    .consoleCmdIOParam = SYS_CMD_SINGLE_CHARACTER_READ_CONSOLE_IO_PARAM,
	.consoleIndex = 0,
};


static const SYS_DEBUG_INIT debugInit =
{
    .moduleInit = {0},
    .errorLevel = SYS_DEBUG_GLOBAL_ERROR_LEVEL,
    .consoleIndex = 0,
};





// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************

/* MISRAC 2012 deviation block end */

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{

    /* MISRAC 2012 deviation block start */
    /* MISRA C-2012 Rule 2.2 deviated in this file.  Deviation record ID -  H3_MISRAC_2012_R_2_2_DR_1 */

    NVMCTRL_Initialize( );

  
    PORT_Initialize();

    CLOCK_Initialize();




    TC1_TimerInitialize();

    TC0_TimerInitialize();

	SDHC1_Initialize();

    TC2_TimerInitialize();

    ADC1_Initialize();
    SERCOM3_I2C_Initialize();

    SERCOM1_USART_Initialize();

    EVSYS_Initialize();

    SERCOM7_USART_Initialize();

	SYSTICK_TimerInitialize();
    DMAC_Initialize();

    SERCOM5_USART_Initialize();



    /* MISRAC 2012 deviation block start */
    /* Following MISRA-C rules deviated in this block  */
    /* MISRA C-2012 Rule 11.3 - Deviation record ID - H3_MISRAC_2012_R_11_3_DR_1 */
    /* MISRA C-2012 Rule 11.8 - Deviation record ID - H3_MISRAC_2012_R_11_8_DR_1 */


   /* Initialize the MIIM Driver Instance 0*/
   sysObj.drvMiim_0 = DRV_MIIM_OBJECT_BASE_Default.DRV_MIIM_Initialize(DRV_MIIM_DRIVER_INDEX_0, (const SYS_MODULE_INIT *) &drvMiimInitData_0); 

   sysObj.drvSDMMC0 = DRV_SDMMC_Initialize(DRV_SDMMC_INDEX_0,(SYS_MODULE_INIT *)&drvSDMMC0InitData);


    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
    H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);
    
    /* MISRAC 2012 deviation block end */
    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&sysConsole0Init);
   /* MISRAC 2012 deviation block end */
    SYS_CMD_Initialize((SYS_MODULE_INIT*)&sysCmdInit);

    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    /* MISRAC 2012 deviation block end */


   /* Network Presentation Layer Initialization */
   sysObj.netPres = NET_PRES_Initialize(0, (SYS_MODULE_INIT*)&netPresInitData);
   /* TCPIP Stack Initialization */
   
   //sysObj.tcpip = TCPIP_STACK_Init();
   //SYS_ASSERT(sysObj.tcpip != SYS_MODULE_OBJ_INVALID, "TCPIP_STACK_Init Failed" );


    CRYPT_WCCB_Initialize();
    /*** File System Service Initialization Code ***/
    (void) SYS_FS_Initialize( (const void *) sysFSInit );


    /* MISRAC 2012 deviation block end */
    APP_HEATPUMP_COMM_Initialize();
    APP_DISPLAY_COMM_Initialize();
    APP_HEATING_AND_HOT_WATER_Initialize();
    APP_IN_OUTPUTS_Initialize();
    APP_I2C_TASKS_Initialize();
    APP_LOGGING_TASKS_Initialize();
    APP_SD_CARD_TASKS_Initialize();


    NVIC_Initialize();

    /* MISRAC 2012 deviation block end */
}

/*******************************************************************************
 End of File
*/
