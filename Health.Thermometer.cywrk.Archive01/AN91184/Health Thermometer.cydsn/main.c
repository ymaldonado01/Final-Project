/****************************************************************************
* 
*****************************************************************************/
#include <project.h>
#include "CommonFunctions.h"
#include "Temperature.h"
#include "BLE_HTSS.h"

/*****************************************************************************
* Function Name: main()
******************************************************************************
* Summary:
* Central function which controls the application flow
*
* Parameters:
* None
*
* Return:
* None
*
* Theory:
* Central function which is entered on power up. This function controls
* the complete application which includes BLE processing, temperature 
* measurement and power mode transitions.
*
* Side Effects:
* None
*
* Note:
*
*****************************************************************************/
int main()
{
   
    
    /* Powerstate indicators of BLESS */
    CYBLE_LP_MODE_T lpMode = CYBLE_BLESS_DEEPSLEEP;
    CYBLE_BLESS_STATE_T blessState = CYBLE_BLESS_STATE_DEEPSLEEP;
    
    /* Local variable used to store temperature information */
    uint32 temperature;
    
 
    /* Enable global interrupt, required for BLESS operation */
    CyGlobalIntEnable; 
    
    /* Initialize the complete system */
    InitializeSystem();
    
    /* Infinite loop */
    for(;;)
    {
        /* Process all pending BLE events in the stack */
        CyBle_ProcessEvents();
        
        /***********************************************************************
        * Wait for connection established with Central device
        ***********************************************************************/
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            /* Process all pending BLE events in the stack */
            CyBle_ProcessEvents();
            /* Periodically measure temperature and send results to the Client */
            if(SystemFlag & WAKEUP_SOURCE_WDT)
            {
                /* Clear WDT wakeup source flag */
                SystemFlag &= ~WAKEUP_SOURCE_WDT;
                /* Wakeup the system from deep sleep */
                WakeupFromDeepSleep();
                /* Measure temperature */
                temperature = ProcessTemperature();
                /* Send temperature information over BLE */
                ProcessBLE(temperature);    
                     

                
            }
        }
        
        if(CyBle_GetState() != CYBLE_STATE_INITIALIZING)
        {
            /* Disable all hardware blocks */
            PrepareForDeepSleep();
            /* Enter Deep Sleep mode between connection intervals */
            lpMode = CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
            
            /* Disable global interrupts to avoid race condition */
            CyGlobalIntDisable;
            blessState = CyBle_GetBleSsState();

            /* Try putting system in DeepSleep mode if BLESS succesfully entered Deep Sleep mode*/
            if(lpMode == CYBLE_BLESS_DEEPSLEEP) 
            {   
                /* If BLESS is in Deep Sleep or is in the process of waking up from Deep Sleep,
                 * put system in Deep Sleep mode */
                if(blessState == CYBLE_BLESS_STATE_ECO_ON || blessState == CYBLE_BLESS_STATE_DEEPSLEEP)
                {
                    CySysPmDeepSleep();
                }
            }
            /* If BLESS is in Active state */
            else
            {
                /* If BLESS Tx/Rx Event is not complete, reduce IMO and put CPU to Sleep */
                if(blessState != CYBLE_BLESS_STATE_EVENT_CLOSE)
                {
                    CySysClkWriteImoFreq(IMO_FREQUENCY_3MHZ);
                    CySysPmSleep();
                    CySysClkWriteImoFreq(IMO_FREQUENCY_12MHZ);
                }
            }
            /* Enable interrupts for normal operation */
            CyGlobalIntEnable;
            
           
        }
        
        /* If Hibernate is enabled then put system in hibernate state
        if(SystemFlag & ENABLE_HIBERNATE)
        {
            Enable ISR for the pin to wakeup the device from hibernate
            Wakeup_ISR_Start();
            
            Put sytem to hibernate 
            CySysPmHibernate();
        }
        */
    }
}


    
