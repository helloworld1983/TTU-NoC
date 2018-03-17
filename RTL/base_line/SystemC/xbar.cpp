// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "xbar.h"

// This circuit is fully combinational.

void XBAR::logic_1()
{
    switch (sel.read())
    {
        case 1:
            Data_out.write(Local_in.read());
            break;
            
        case 2:
            Data_out.write(South_in.read());
            break;
            
        case 4:
            Data_out.write(West_in.read());
            break;
            
        case 8:
            Data_out.write(East_in.read());
            break;
            
        default: // North input selected or invalid "sel" value
            Data_out.write(North_in.read());
            break;
    }
}

SC_MODULE_EXPORT(XBAR);
