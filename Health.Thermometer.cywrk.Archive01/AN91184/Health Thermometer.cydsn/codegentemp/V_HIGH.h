/*******************************************************************************
* File Name: V_HIGH.h  
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

#if !defined(CY_PINS_V_HIGH_H) /* Pins V_HIGH_H */
#define CY_PINS_V_HIGH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "V_HIGH_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    V_HIGH_Write(uint8 value) ;
void    V_HIGH_SetDriveMode(uint8 mode) ;
uint8   V_HIGH_ReadDataReg(void) ;
uint8   V_HIGH_Read(void) ;
uint8   V_HIGH_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V_HIGH_DRIVE_MODE_BITS        (3)
#define V_HIGH_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - V_HIGH_DRIVE_MODE_BITS))

#define V_HIGH_DM_ALG_HIZ         (0x00u)
#define V_HIGH_DM_DIG_HIZ         (0x01u)
#define V_HIGH_DM_RES_UP          (0x02u)
#define V_HIGH_DM_RES_DWN         (0x03u)
#define V_HIGH_DM_OD_LO           (0x04u)
#define V_HIGH_DM_OD_HI           (0x05u)
#define V_HIGH_DM_STRONG          (0x06u)
#define V_HIGH_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define V_HIGH_MASK               V_HIGH__MASK
#define V_HIGH_SHIFT              V_HIGH__SHIFT
#define V_HIGH_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_HIGH_PS                     (* (reg32 *) V_HIGH__PS)
/* Port Configuration */
#define V_HIGH_PC                     (* (reg32 *) V_HIGH__PC)
/* Data Register */
#define V_HIGH_DR                     (* (reg32 *) V_HIGH__DR)
/* Input Buffer Disable Override */
#define V_HIGH_INP_DIS                (* (reg32 *) V_HIGH__PC2)


#if defined(V_HIGH__INTSTAT)  /* Interrupt Registers */

    #define V_HIGH_INTSTAT                (* (reg32 *) V_HIGH__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define V_HIGH_DRIVE_MODE_SHIFT       (0x00u)
#define V_HIGH_DRIVE_MODE_MASK        (0x07u << V_HIGH_DRIVE_MODE_SHIFT)


#endif /* End Pins V_HIGH_H */


/* [] END OF FILE */
