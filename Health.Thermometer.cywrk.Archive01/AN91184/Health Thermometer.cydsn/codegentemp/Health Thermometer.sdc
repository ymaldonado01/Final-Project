# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Shahed\Desktop\Yobely- Health Thermometer.cywrk.Archive01\AN91184\Health Thermometer.cydsn\Health Thermometer.cyprj
# Date: Wed, 07 Dec 2016 00:05:56 GMT
#set_units -time ns
create_clock -name {ADC_intClock(FFB)} -period 666.66666666666663 -waveform {0 333.333333333333} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {CyHFCLK} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/hfclk}]]
create_generated_clock -name {ADC_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 17} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 12001 24001} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 12001 24001} [list [get_pins {ClockBlock/udb_div_3}]]
create_clock -name {CyIMO} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CySYSCLK} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/sysclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFCLK} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyRouted1} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/dsi_in_0}]]


# Component constraints for C:\Users\Shahed\Desktop\Yobely- Health Thermometer.cywrk.Archive01\AN91184\Health Thermometer.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Shahed\Desktop\Yobely- Health Thermometer.cywrk.Archive01\AN91184\Health Thermometer.cydsn\Health Thermometer.cyprj
# Date: Wed, 07 Dec 2016 00:05:50 GMT
