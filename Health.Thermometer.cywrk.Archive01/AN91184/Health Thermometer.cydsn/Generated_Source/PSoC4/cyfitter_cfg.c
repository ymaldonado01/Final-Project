/*******************************************************************************
* FILENAME: cyfitter_cfg.c
* PSoC Creator  3.1 SP3
*
* Description:
* This file is automatically generated by PSoC Creator with device 
* initialization code.  Except for the user defined sections in
* CyClockStartupError(), this file should not be modified.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
#include <cyfitter_cfg.h>


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYPACKED 
    #define CYPACKED_ATTR __attribute__ ((packed))
    #define CYALIGNED __attribute__ ((aligned))
    #define CY_CFG_UNUSED __attribute__ ((unused))
    #define CY_CFG_SECTION __attribute__ ((section(".psocinit")))
    
    #if defined(__ARMCC_VERSION)
        #define CY_CFG_MEMORY_BARRIER() __memory_changed()
    #else
        #define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
    #endif
    
#elif defined(__ICCARM__)
    #include <intrinsics.h>

    #define CYPACKED __packed
    #define CYPACKED_ATTR 
    #define CYALIGNED _Pragma("data_alignment=4")
    #define CY_CFG_UNUSED _Pragma("diag_suppress=Pe177")
    #define CY_CFG_SECTION _Pragma("location=\".psocinit\"")
    
    #define CY_CFG_MEMORY_BARRIER() __DMB()
    
#else
    #error Unsupported toolchain
#endif


CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n);
CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n)
{
	(void)memset(s, 0, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}



/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u

#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* `#START CyClockStartupError` */

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

    /* `#END` */

    /* If nothing else, stop here since the clocks have not started         */
    /* correctly.                                                           */
    while(1) {}
}
#endif

#define CY_CFG_BASE_ADDR_COUNT 4u
CYPACKED typedef struct
{
	uint8 offset;
	uint8 value;
} CYPACKED_ATTR cy_cfg_addrvalue_t;



/*******************************************************************************
* Function Name: cfg_write_bytes32
********************************************************************************
* Summary:
*  This function is used for setting up the chip configuration areas that
*  contain relatively sparse data.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[]);
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[])
{
	/* For 32-bit little-endian architectures */
	uint32 i, j = 0u;
	for (i = 0u; i < CY_CFG_BASE_ADDR_COUNT; i++)
	{
		uint32 baseAddr = addr_table[i];
		uint8 count = (uint8)baseAddr;
		baseAddr &= 0xFFFFFF00u;
		while (count != 0u)
		{
			CY_SET_XTND_REG8((void CYFAR *)(baseAddr + data_table[j].offset), data_table[j].value);
			j++;
			count--;
		}
	}
}

/*******************************************************************************
* Function Name: SetIMOBGTrims
********************************************************************************
*
* Summary:
*   Performs the configuration of the bandgap trim for the IMO based on the given
*   expected frequency of the IMO. 
*
* Parameters:
*   imoFreq: Frequency for operation of the IMO.
*
* Return:
*   void
*
*******************************************************************************/
static void SetIMOBGTrims(uint8 imoFreq);
CY_CFG_SECTION
static void SetIMOBGTrims(uint8 imoFreq)
{
	CYPACKED typedef struct {
		uint8 freq;
		uint8 absolute;
		uint8 tmpco;
	} CYPACKED_ATTR imo_trim_entry_t;

	CYPACKED typedef struct {
		imo_trim_entry_t entries[4];
	} CYPACKED_ATTR imo_trim_table_t;

	static const imo_trim_table_t *imo_trim_table = (const imo_trim_table_t *)CYREG_SFLASH_IMO_MAXF0;
	static const uint32 IMO_TRIM_FREQ_TABLE_ENTRIES = sizeof(imo_trim_table->entries)/sizeof(imo_trim_table->entries[0]);

	int32 imoTrimIndex;
	uint8 setAbs;
	uint8 setTmpCo;

	/* Traverse the SFLASH IMO frequency-dependent bandgap trim table to
	 * locate the appropriate value to trim the IMO bandgap based on freq. */
	setAbs = CY_GET_REG8((const void *)CYREG_SFLASH_IMO_ABS4);
	setTmpCo = CY_GET_REG8((const void *)CYREG_SFLASH_IMO_TMPCO4);
	for (imoTrimIndex = ((int32)IMO_TRIM_FREQ_TABLE_ENTRIES)-1;
	     (imoTrimIndex >= 0) && (imoFreq <= imo_trim_table->entries[imoTrimIndex].freq);
	     imoTrimIndex--)
	{
		setAbs = imo_trim_table->entries[imoTrimIndex].absolute;
		setTmpCo = imo_trim_table->entries[imoTrimIndex].tmpco;
	}

	CY_SET_REG32((void *)CYREG_PWR_BG_TRIM4, setAbs);
	CY_SET_REG32((void *)CYREG_PWR_BG_TRIM5, setTmpCo);
}



/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*   Performs the initialization of all of the clocks in the device based on the
*   settings in the Clock tab of the DWR.  This includes enabling the requested
*   clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void ClockSetup(void);
CY_CFG_SECTION
static void ClockSetup(void)
{

	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG32((void CYXDATA *)(CYREG_CPUSS_FLASH_CTL), (0x0012u));
	/* Trim IMO BG based on desired frequency. */
	SetIMOBGTrims(12u);

	/* Going less than or equal to 24MHz, so update the clock speed then adjust trim value. */
	CY_SET_REG32((void CYXDATA *)(CYREG_CLK_IMO_TRIM2), (12u));
	CyDelayCycles(5u);
	CY_SET_REG32((void CYXDATA *)(CYREG_CLK_IMO_TRIM1), (CY_GET_REG8((void *)CYREG_SFLASH_IMO_TRIM09)));
	CyDelayUs(5u);

	/* Start the WCO */
	CySysClkWcoStart();
	CyDelay(500u); /* WCO may take up to 500ms to start */
	(void)CySysClkWcoSetPowerMode(CY_SYS_CLK_WCO_LPM);    /* Switch to the low power mode */
	/* CYDEV_CLK_ILO_CONFIG Starting address: CYDEV_CLK_ILO_CONFIG */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_ILO_CONFIG), 0x80000006u);

	/* CYDEV_WDT_CONFIG Starting address: CYDEV_WDT_CONFIG */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_WDT_CONFIG), 0x40000000u);


	CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLERD_BB_XO_CAPTRIM), 0x00002D6Au);
	/* Disable Crystal Stable Interrupt before enabling ECO */
	CY_SET_REG32((void*)CYREG_BLE_BLESS_LL_DSM_CTRL, CY_GET_REG32((void*)CYREG_BLE_BLESS_LL_DSM_CTRL) & (~(uint32)0x08u));
	/* Start the ECO and do not check status since it is not needed for HFCLK */
	(void)CySysClkEcoStart(2000u);
	CyDelayUs(1500u); /* Wait to stabalize */

	/* Setup phase aligned clocks */
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL02, 0x002EDF00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF42u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL01, 0x002EDF00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF41u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL00, 0x00000700u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF40u);

	/* CYDEV_CLK_IMO_CONFIG Starting address: CYDEV_CLK_IMO_CONFIG */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_IMO_CONFIG), 0xA6000000u);

	/* CYDEV_PERI_PCLK_CTL14 Starting address: CYDEV_PERI_PCLK_CTL14 */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_PERI_PCLK_CTL14), 0x00000042u);

	/* CYDEV_PERI_PCLK_CTL12 Starting address: CYDEV_PERI_PCLK_CTL12 */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_PERI_PCLK_CTL12), 0x00000041u);

	/* CYDEV_PERI_PCLK_CTL06 Starting address: CYDEV_PERI_PCLK_CTL06 */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_PERI_PCLK_CTL06), 0x00000040u);

	/* Set Flash Cycles based on newly configured 12.00MHz HFCLK. */
	CY_SET_REG32((void CYXDATA *)(CYREG_CPUSS_FLASH_CTL), (0x0000u));
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTBM0_DFT_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTBM1_DFT_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_DSAB_DSAB_CTRL, 0x00000000u);
	SetAnalogRoutingPumps(1);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint32 regValue = CY_GET_XTND_REG32((void *)(CYREG_SAR_PUMP_CTRL));
	if (enabled != 0u)
	{
		regValue |= 0x80000000u;
	}
	else
	{
		regValue &= ~0x80000000u;
	}
	CY_SET_XTND_REG32((void *)(CYREG_SAR_PUMP_CTRL), regValue);
}

#define CY_AMUX_UNUSED CYREG_CM0_ROM_DWT
int8 AMuxSeq_CYAMUXSIDE_B_curChannel = -1;

void AMuxSeq_CYAMUXSIDE_B_DisconnectAll(void)
{
	AMuxSeq_CYAMUXSIDE_B_curChannel = -1;
	CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x200u));
	CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x400u));
	CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x400u));
}

void AMuxSeq_CYAMUXSIDE_B_Next(void)
{
	AMuxSeq_CYAMUXSIDE_B_curChannel++;
	switch (AMuxSeq_CYAMUXSIDE_B_curChannel)
	{
	case 4: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_B_curChannel = 4;
	case 5: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_B_curChannel = 5;
	case 6: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_B_curChannel = 6;
	case 7: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_B_curChannel = 7;
	case 3:
	default:
		AMuxSeq_CYAMUXSIDE_B_curChannel = 0;
	case 0:
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x400u));
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH0, (0x200u));
		break;
	case 1:
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x200u));
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH0, (0x400u));
		break;
	case 2:
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x400u));
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH0, (0x400u));
		break;
	}
}

int8 AMuxSeq_CYAMUXSIDE_A_curChannel = -1;

void AMuxSeq_CYAMUXSIDE_A_DisconnectAll(void)
{
	AMuxSeq_CYAMUXSIDE_A_curChannel = -1;
	CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x01u));
	CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x02u));
	CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x04u));
}

void AMuxSeq_CYAMUXSIDE_A_Next(void)
{
	AMuxSeq_CYAMUXSIDE_A_curChannel++;
	switch (AMuxSeq_CYAMUXSIDE_A_curChannel)
	{
	case 4: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_A_curChannel = 4;
	case 5: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_A_curChannel = 5;
	case 6: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_A_curChannel = 6;
	case 7: /* to force jump table (not executed) */
		AMuxSeq_CYAMUXSIDE_A_curChannel = 7;
	case 3:
	default:
		AMuxSeq_CYAMUXSIDE_A_curChannel = 0;
	case 0:
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x04u));
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH0, (0x01u));
		break;
	case 1:
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x01u));
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH0, (0x02u));
		break;
	case 2:
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH_CLEAR0, (0x02u));
		CY_SET_REG32((void CYXDATA *)CYREG_SAR_MUX_SWITCH0, (0x04u));
		break;
	}
}



/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_SECTION
void cyfitter_cfg(void)
{
	/* Disable interrupts by default. Let user enable if/when they want. */
	CyGlobalIntDisable;

	CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_LL_DSM_CTRL), 0x00000000u);

	{
		static const uint32 CYCODE cy_cfg_addr_table[] = {
			0x400F0002u, /* Base address: 0x400F0000 Count: 2 */
			0x400F324Fu, /* Base address: 0x400F3200 Count: 79 */
			0x400F3328u, /* Base address: 0x400F3300 Count: 40 */
			0x400F6002u, /* Base address: 0x400F6000 Count: 2 */
		};

		static const cy_cfg_addrvalue_t CYCODE cy_cfg_data_table[] = {
			{0x82u, 0x0Du},
			{0x83u, 0x0Du},
			{0x0Fu, 0x01u},
			{0x14u, 0x01u},
			{0x1Au, 0x03u},
			{0x23u, 0x01u},
			{0x2Eu, 0x04u},
			{0x30u, 0x01u},
			{0x32u, 0x02u},
			{0x35u, 0x01u},
			{0x36u, 0x04u},
			{0x3Fu, 0x10u},
			{0x40u, 0x10u},
			{0x41u, 0x05u},
			{0x45u, 0xD1u},
			{0x46u, 0x02u},
			{0x48u, 0x07u},
			{0x49u, 0xFFu},
			{0x4Au, 0xFFu},
			{0x4Bu, 0xFFu},
			{0x4Du, 0xA0u},
			{0x4Fu, 0x04u},
			{0x50u, 0x18u},
			{0x52u, 0x80u},
			{0x54u, 0x05u},
			{0x58u, 0x04u},
			{0x59u, 0x04u},
			{0x5Au, 0x04u},
			{0x5Bu, 0x04u},
			{0x5Cu, 0x03u},
			{0x5Du, 0x33u},
			{0x5Fu, 0x01u},
			{0x60u, 0x40u},
			{0x62u, 0xC0u},
			{0x64u, 0x40u},
			{0x65u, 0x40u},
			{0x66u, 0xC0u},
			{0x68u, 0xC0u},
			{0x6Au, 0xC0u},
			{0x6Cu, 0xC0u},
			{0x6Eu, 0xC0u},
			{0x83u, 0x01u},
			{0x8Cu, 0x01u},
			{0x92u, 0x04u},
			{0x9Au, 0x04u},
			{0xA6u, 0x03u},
			{0xB0u, 0x02u},
			{0xB4u, 0x04u},
			{0xB5u, 0x01u},
			{0xB6u, 0x01u},
			{0xB7u, 0x01u},
			{0xBEu, 0x10u},
			{0xC0u, 0x10u},
			{0xC1u, 0x05u},
			{0xC5u, 0xD1u},
			{0xC7u, 0x20u},
			{0xC8u, 0x23u},
			{0xC9u, 0xFFu},
			{0xCAu, 0xFFu},
			{0xCBu, 0xFFu},
			{0xCDu, 0xA0u},
			{0xCFu, 0x04u},
			{0xD0u, 0x18u},
			{0xD2u, 0x80u},
			{0xD4u, 0x05u},
			{0xD8u, 0x04u},
			{0xD9u, 0x04u},
			{0xDAu, 0x04u},
			{0xDBu, 0x04u},
			{0xDCu, 0x11u},
			{0xDDu, 0x11u},
			{0xDFu, 0x01u},
			{0xE0u, 0x40u},
			{0xE2u, 0xC0u},
			{0xE4u, 0x40u},
			{0xE5u, 0x40u},
			{0xE6u, 0xC0u},
			{0xE8u, 0xC0u},
			{0xEAu, 0xC0u},
			{0xECu, 0xC0u},
			{0xEEu, 0xC0u},
			{0x00u, 0x40u},
			{0x09u, 0x22u},
			{0x0Eu, 0x20u},
			{0x0Fu, 0x08u},
			{0x10u, 0x20u},
			{0x17u, 0x80u},
			{0x18u, 0x40u},
			{0x19u, 0x40u},
			{0x1Au, 0x04u},
			{0x1Du, 0x80u},
			{0x1Eu, 0x60u},
			{0x1Fu, 0x80u},
			{0x20u, 0x01u},
			{0x21u, 0x20u},
			{0x27u, 0x08u},
			{0x2Fu, 0x80u},
			{0x38u, 0x02u},
			{0x3Fu, 0x80u},
			{0x40u, 0x01u},
			{0x45u, 0x80u},
			{0x48u, 0x22u},
			{0x49u, 0x01u},
			{0x4Fu, 0x89u},
			{0x50u, 0x02u},
			{0x51u, 0x02u},
			{0x57u, 0x40u},
			{0x59u, 0x41u},
			{0x5Au, 0x04u},
			{0x5Eu, 0x40u},
			{0x5Fu, 0x09u},
			{0x70u, 0x01u},
			{0x77u, 0x80u},
			{0xC0u, 0x01u},
			{0xC2u, 0x6Au},
			{0xC4u, 0x84u},
			{0xCAu, 0x80u},
			{0xCEu, 0x11u},
			{0xD0u, 0x18u},
			{0xD2u, 0x18u},
			{0xD6u, 0xDBu},
			{0x01u, 0x0Au},
			{0x10u, 0x0Au},
		};



		CYPACKED typedef struct {
			void CYFAR *address;
			uint16 size;
		} CYPACKED_ATTR cfg_memset_t;

		static const cfg_memset_t CYCODE cfg_memset_list [] = {
			/* address, size */
			{(void CYFAR *)(CYDEV_UDB_P0_U0_BASE), 1024u},
			{(void CYFAR *)(CYDEV_UDB_DSI0_BASE), 1024u},
		};

		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0u; i < (sizeof(cfg_memset_list)/sizeof(cfg_memset_list[0])); i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, (size_t)(uint32)(ms->size));
		}

		cfg_write_bytes32(cy_cfg_addr_table, cy_cfg_data_table);

		/* HSIOM Starting address: CYDEV_HSIOM_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_HSIOM_BASE), 0xEE000000u);

		/* IOPINS0_0 Starting address: CYDEV_GPIO_PRT0_DR */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT0_PC), 0x00D80000u);

		/* IOPINS0_2 Starting address: CYDEV_GPIO_PRT2_DR */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT2_PC), 0x00180000u);

		/* IOPINS0_3 Starting address: CYDEV_GPIO_PRT3_DR */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT3_DR), 0x00000002u);
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT3_PC), 0x00C00186u);
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT3_PC2), 0x00000002u);

		/* UDB_PA_0 Starting address: CYDEV_UDB_PA0_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_UDB_PA0_BASE), 0x00990000u);

		/* UDB_PA_2 Starting address: CYDEV_UDB_PA2_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_UDB_PA2_BASE), 0x00990000u);

		/* UDB_PA_3 Starting address: CYDEV_UDB_PA3_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_UDB_PA3_BASE), 0x00990000u);

		/* Enable digital routing */
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL, CY_GET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL) | 0x02u);

		/* Enable UDB array */
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDBIF_WAIT_CFG, (uint8)((CY_GET_XTND_REG8((void *)CYREG_UDB_UDBIF_WAIT_CFG) & 0xC3u) | 0x14u));
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL, (uint8)(CY_GET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL) | 0x16u));
	}

	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

}
