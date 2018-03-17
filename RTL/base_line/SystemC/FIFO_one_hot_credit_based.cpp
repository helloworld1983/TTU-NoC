// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "FIFO_one_hot_credit_based.h"


// ---------------------------------------------------------------
//                            block diagram of the FIFO!
//
//
// ---------------------------------------------------------------
//           circular buffer structure
//                                            <--- WriteP
//                       ---------------------------------
//                       |   3   |   2   |   1   |   0   |
//                       ---------------------------------
//                                            <--- readP
// ---------------------------------------------------------------


// The sequential part

void FIFO_credit_based::FIFO_sequential_proc()
{
    if (reset.read() == 0) // Synchronous reset ?!
    {        
        read_pointer.write  ((sc_uint<4>) 1);
        write_pointer.write ((sc_uint<4>) 1);
        
        FIFO_MEM_1.write (0);
        FIFO_MEM_2.write (0);
        FIFO_MEM_3.write (0);
        FIFO_MEM_4.write (0);
        
        credit_out.write(0);
    }
    
    else if (clk.event() && clk.read() == 1) // At the rising edge of clock do the following
    {
        write_pointer.write (write_pointer_in.read());
        read_pointer.write  (read_pointer_in.read());
        credit_out.write(0);
        
        if (write_en.read() == 1)
        {
            // Write into the FIFO memory
            FIFO_MEM_1.write (FIFO_MEM_1_in.read());
            FIFO_MEM_2.write (FIFO_MEM_2_in.read());
            FIFO_MEM_3.write (FIFO_MEM_3_in.read());
            FIFO_MEM_4.write (FIFO_MEM_4_in.read());
        }
                
        if (read_en.read() == 1)
            credit_out.write(1);
    }
}


// Anything below here is pure combinational

// Combinatorial part


void FIFO_credit_based::logic_1()
{
    switch ((sc_uint<4>) write_pointer.read())
    {
        case 1:
            FIFO_MEM_1_in = RX.read();
            FIFO_MEM_2_in = FIFO_MEM_2.read();
            FIFO_MEM_3_in = FIFO_MEM_3.read();
            FIFO_MEM_4_in = FIFO_MEM_4.read();
            break;
            
        case 2:
            FIFO_MEM_1_in = FIFO_MEM_1.read();
            FIFO_MEM_2_in = RX.read();
            FIFO_MEM_3_in = FIFO_MEM_3.read();
            FIFO_MEM_4_in = FIFO_MEM_4.read();
            break;
            
        case 4:
            FIFO_MEM_1_in = FIFO_MEM_1.read();
            FIFO_MEM_2_in = FIFO_MEM_2.read();
            FIFO_MEM_3_in = RX.read();
            FIFO_MEM_4_in = FIFO_MEM_4.read();
            break;
            
        case 8:
            FIFO_MEM_1_in = FIFO_MEM_1.read();
            FIFO_MEM_2_in = FIFO_MEM_2.read();
            FIFO_MEM_3_in = FIFO_MEM_3.read();
            FIFO_MEM_4_in = RX.read();
            break;
            
        default:
            FIFO_MEM_1_in = FIFO_MEM_1.read();
            FIFO_MEM_2_in = FIFO_MEM_2.read();
            FIFO_MEM_3_in = FIFO_MEM_3.read();
            FIFO_MEM_4_in = FIFO_MEM_4.read();
            break;
    }
    
//    cout << "FIFO read this from input : " << (sc_bv<32>) RX.read() << " \n";
}


void FIFO_credit_based::logic_2()
{
    switch ((sc_uint<4>) read_pointer.read())
    {
        case 0b0001:
            Data_out.write(FIFO_MEM_1.read());
            break;
            
        case 0b0010:
            Data_out.write(FIFO_MEM_2.read());
            break;
            
        case 0b0100:
            Data_out.write(FIFO_MEM_3.read());
            break;
            
        case 0b1000:
            Data_out.write(FIFO_MEM_4.read());
            break;
            
        default:
            Data_out.write(FIFO_MEM_1.read()); // ?!
            break;
    }
    
//    cout << "FIFO sent this it its output : " << (sc_bv<32>) Data_out.read() << " \n";
}


void FIFO_credit_based::logic_3()
{
    read_en.write ((read_en_N.read() || read_en_E.read() || read_en_W.read() || read_en_S.read() || read_en_L.read()) && !empty.read());
}


void FIFO_credit_based::logic_8()
{
    empty_out.write (empty.read());
}


void FIFO_credit_based::logic_4()
{
    sc_uint<4> write_pointer_tmp = write_pointer.read();
    
    if (write_en.read() == 1)
        write_pointer_in.write ((write_pointer_tmp.range(2,0) , write_pointer_tmp[3]));
    else
        write_pointer_in.write (write_pointer.read());
}


void FIFO_credit_based::logic_5()
{
    sc_uint<4> read_pointer_tmp = read_pointer.read();
    
    if (read_en.read()==1 && empty.read()==0)
        read_pointer_in.write ((read_pointer_tmp.range(2,0) , read_pointer_tmp[3]));
    else
        read_pointer_in.write (read_pointer.read());
}


void FIFO_credit_based::logic_6()
{
    if (valid_in.read()==1 && full.read()==0)
        write_en.write (1);
    else
        write_en.write (0);
}


void FIFO_credit_based::logic_7()
{
    sc_uint<4> read_pointer_tmp = read_pointer.read();
    
    if (read_pointer.read() == write_pointer.read())
        empty.write (1);
    else
        empty.write (0);
    
    if (write_pointer.read() == (read_pointer_tmp[0] , read_pointer_tmp.range(3,1)))
        full.write (1);
    else
        full.write (0);
}

SC_MODULE_EXPORT(FIFO_credit_based);

