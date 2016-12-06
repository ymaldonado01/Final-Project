/*******************************************************************************
* File Name: V_THERM.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_V_THERM_H) /* Pins V_THERM_H */
#define CY_PINS_V_THERM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "V_THERM_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    V_THERM_Write(uint8 value) ;
void    V_THERM_SetDriveMode(uint8 mode) ;
uint8   V_THERM_ReadDataReg(void) ;
uint8   V_THERM_Read(void) ;
uint8   V_THERM_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V_THERM_DRIVE_MODE_BITS        (3)
#define V_THERM_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - V_THERM_DRIVE_MODE_BITS))

#define V_THERM_DM_ALG_HIZ         (0x00u)
#define V_THERM_DM_DIG_HIZ         (0x01u)
#define V_THERM_DM_RES_UP          (0x02u)
#define V_THERM_DM_RES_DWN         (0x03u)
#define V_THERM_DM_OD_LO           (0x04u)
#define V_THERM_DM_OD_HI           (0x05u)
#define V_THERM_DM_STRONG          (0x06u)
#define V_THERM_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define V_THERM_MASK               V_THERM__MASK
#define V_THERM_SHIFT              V_THERM__SHIFT
#define V_THERM_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_THERM_PS                     (* (reg32 *) V_THERM__PS)
/* Port Configuration */
#define V_THERM_PC                     (* (reg32 *) V_THERM__PC)
/* Data Register */
#define V_THERM_DR                     (* (reg32 *) V_THERM__DR)
/* Input Buffer Disable Override */
#define V_THERM_INP_DIS                (* (reg32 *) V_THERM__PC2)


#if defined(V_THERM__INTSTAT)  /* Interrupt Registers */

    #define V_THERM_INTSTAT                (* (reg32 *) V_THERM__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define V_THERM_DRIVE_MODE_SHIFT       (0x00u)
#define V_THERM_DRIVE_MODE_MASK        (0x07u << V_THERM_DRIVE_MODE_SHIFT)


#endif /* End Pins V_THERM_H */


/* [] END OF FILE */
