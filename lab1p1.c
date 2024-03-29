// ******************************************************************************************* //
// Include file for PIC24FJ64GA002 microcontroller. This include file defines
// MACROS for special function registers (SFR) and control bits within those
// registers.

#include "p24fj64ga002.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
// This option can be set by selecting "Configuration Bits..." under the Configure
// menu in MPLAB.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

// ******************************************************************************************* //
// Configuration bits for CONFIG2 settings.
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
// This option can be set by selecting "Configuration Bits..." under the Configure
// menu in MPLAB.

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

void DebounceDelay() {
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0);
    T1CONbits.TON = 0;
    TMR1 = 0;
    IFS0bits.T1IF = 0;
}

int main(void)
{
	// ****************************************************************************** //

	// TODO: Configure AD1PCFG register for configuring input pins between analog input
	// and digital IO.
        AD1PCFGbits.PCFG4 = 1;

	// TODO: Configure TRIS register bits for Right and Left LED outputs.
        TRISAbits.TRISA0 = 0;   //Right (green/run)
        TRISAbits.TRISA1 = 0;   //Left (red/stop)


	// TODO: Configure LAT register bits to initialize Right LED to on.
        LATAbits.LATA0 = 0;     //Turn Right (green/run) one on
        LATAbits.LATA1 = 1;     //Turn Left (red/stop) one off


	// TODO: Configure ODC register bits to use open drain configuration for Right
	// and Left LED output.
        ODCAbits.ODA0 = 1;
        ODCAbits.ODA1 = 1;

	// TODO: Configure TRIS register bits for swtich input.
        TRISBbits.TRISB2 = 1;   //switch
        TRISBbits.TRISB

	// TODO: Configure CNPU register bits to enable internal pullup resistor for switch
	// input.
        CNPU1bits.CN6PUE = 1;

	// TODO: Setup Timer 1 to use internal clock (Fosc/2).
        T1CONbits.TCS=0;

	// TODO: Setup Timer 1's prescaler to 1:256.
        T1CONbits.TCKPS0=1;
        T1CONbits.TCKPS1=1;

 	// TODO: Set Timer 1 to be initially off.
        T1CONbits.TON = 0;

	// TODO: Clear Timer 1 value and reset interrupt flag
        IFS0bits.T1IF = 0;
        TMR1 = 0;

	// TODO: Set Timer 1's period value register to value for 5 ms.
        PR1 = 287;

        int state = 0;
	while(1)
	{
		// TODO: For each distinct button press, alternate which
		// LED is illuminated (on).
            switch(state) {
                case 0:

                    if(PORTBbits.RB2 == 0) {
                        DebounceDelay();
                        if(PORTBbits.RB2 == 0)
                            state = 1;
                    }
                    break;
                case 1:
                    if(PORTBbits.RB2 == 1) {
                        DebounceDelay();
                        if(PORTBbits.RB2 == 1) {
                            LATAbits.LATA0 = !LATAbits.LATA0;
                            LATAbits.LATA1 = !LATAbits.LATA1;
                            state = 0;
                        }
                    }
                    break;
            }


		// TODO: Use DebounceDelay() function to debounce button press
		// and button release in software.

	}
	return 0;
}



// *******************************************************************************************
