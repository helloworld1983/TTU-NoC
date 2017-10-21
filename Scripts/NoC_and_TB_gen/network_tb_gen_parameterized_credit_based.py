# Copyright (C) 2016 Siavoosh Payandeh Azad

from math import ceil, log
import random
import sys

network_dime = 4
data_width = 32
random_dest = False
got_finish_time = False
sim_finish_time = None
bit_reversal = False
get_packet_size = False
packet_size_min = 3
packet_size_max = 8
verbal = False

if '-D'  in sys.argv[1:]:
  network_dime = int(sys.argv[sys.argv.index('-D')+1])


if '-DW' in sys.argv[1:]:
  data_width = int(sys.argv[sys.argv.index('-DW')+1])
  if data_width % 2 != 0:
    raise ValueError("wrong data width. please choose powers of 2. for example 32!")

if '-Rand'  in sys.argv[1:]:
  random_dest = True
  PIR = float(sys.argv[sys.argv.index('-Rand')+1])
  frame_size = int(ceil(1.0/PIR))

if '-BR'  in sys.argv[1:]:
  bit_reversal = True
  PIR = float(sys.argv[sys.argv.index('-BR')+1])
  frame_size = int(ceil(1.0/PIR))

if random_dest and bit_reversal:
  raise ValueError("Can not accept multiple traffic patterns at the same time...")

if '-sim'  in sys.argv[1:]:
  got_finish_time = True
  sim_finish_time = int(sys.argv[sys.argv.index('-sim')+1])

if '-PS'  in sys.argv[1:]:
  get_packet_size = True
  packet_size_min = int(sys.argv[sys.argv.index('-PS')+1])
  packet_size_max = int(sys.argv[sys.argv.index('-PS')+2])

if '-verbal' in sys.argv[1:]:
  verbal = True

file_name = 'tb_network'
if random_dest:
  file_name += '_rand'
elif bit_reversal:
  file_name += '_br'

if '-o'  in sys.argv[1:]:
  file_path = sys.argv[sys.argv.index('-o')+1]
  if ".vhd" not in file_path:
      raise ValueError("wrong file extention. only vhdl files are accepted!")
else:
  file_path = file_name+'_'+str(network_dime)+"x"+str(network_dime)+'.vhd'

noc_file = open(file_path, 'w')


noc_file.write("--Copyright (C) 2016 Siavoosh Payandeh Azad\n")
noc_file.write("------------------------------------------------------------\n")
noc_file.write("-- This file is automatically generated Please do not change!\n")
noc_file.write("-- Here are the parameters:\n")
noc_file.write("-- \t network size x:"+str(network_dime)+"\n")
noc_file.write("-- \t network size y:"+str(network_dime)+"\n")
noc_file.write("-- \t data width:"+str(data_width))
noc_file.write("-- \t traffic pattern:"+str())
noc_file.write("------------------------------------------------------------\n\n")

noc_file.write("library ieee;\n")
noc_file.write("use ieee.std_logic_1164.all;\n")
noc_file.write("use IEEE.STD_LOGIC_ARITH.ALL;\n")
noc_file.write("use IEEE.STD_LOGIC_UNSIGNED.ALL;\n")
noc_file.write("use work.TB_Package.all;\n\n")
noc_file.write("USE ieee.numeric_std.ALL; \n")
noc_file.write("use IEEE.math_real.\"ceil\";\n")
noc_file.write("use IEEE.math_real.\"log2\";\n\n")

noc_file.write("entity tb_network_"+str(network_dime)+"x"+str(network_dime)+" is\n")

noc_file.write("end tb_network_"+str(network_dime)+"x"+str(network_dime)+"; \n")


noc_file.write("\n\n")
noc_file.write("architecture behavior of tb_network_"+str(network_dime)+"x"+str(network_dime)+" is\n\n")

noc_file.write("-- Declaring network component\n")



string_to_print = ""
noc_file.write("component network_"+str(network_dime)+"x"+str(network_dime)+" is\n")

noc_file.write(" generic (DATA_WIDTH: integer := 32; DATA_WIDTH_LV: integer := 11);\n")
noc_file.write("port (reset: in  std_logic; \n")
noc_file.write("\tclk: in  std_logic; \n")

for i in range(network_dime**2):
    noc_file.write("\t--------------\n")
    noc_file.write("\tRX_L_"+str(i)+": in std_logic_vector (DATA_WIDTH-1 downto 0);\n")
    noc_file.write("\tcredit_out_L_"+str(i)+", valid_out_L_"+str(i)+": out std_logic;\n")
    noc_file.write("\tcredit_in_L_"+str(i)+", valid_in_L_"+str(i)+": in std_logic;\n")
    if i == network_dime**2-1 and add_SHMU== False:
        noc_file.write("\tTX_L_"+str(i)+": out std_logic_vector (DATA_WIDTH-1 downto 0)\n")
    else:
        noc_file.write("\tTX_L_"+str(i)+": out std_logic_vector (DATA_WIDTH-1 downto 0);\n")

noc_file.write(string_to_print[:len(string_to_print)-3])
noc_file.write("\n            ); \n")
noc_file.write("end component; \n")

noc_file.write("component flit_tracker is\n")
noc_file.write("    generic (\n")
noc_file.write("        DATA_WIDTH: integer := 32;\n")
noc_file.write("        tracker_file: string :=\"track.txt\"\n")
noc_file.write("    );\n")
noc_file.write("    port (\n")
noc_file.write("        clk: in std_logic;\n")
noc_file.write("        RX: in std_logic_vector (DATA_WIDTH-1 downto 0); \n")
noc_file.write("        valid_in : in std_logic \n")
noc_file.write("    );\n")
noc_file.write("end component;\n")


noc_file.write("\n")
noc_file.write("-- generating bulk signals...\n")
for i in range(0, network_dime*network_dime):
    noc_file.write("\tsignal RX_L_"+str(i)+", TX_L_"+str(i)+":  std_logic_vector ("+str(data_width-1)+" downto 0);\n")
    noc_file.write("\tsignal credit_counter_out_"+str(i)+":  std_logic_vector (1 downto 0);\n")
    noc_file.write("\tsignal credit_out_L_"+str(i)+", credit_in_L_"+str(i)+", valid_in_L_"+str(i)+", valid_out_L_"+str(i) + ": std_logic;\n")

noc_file.write("\t--------------\n")
noc_file.write("\tconstant clk_period : time := 10 ns;\n")
noc_file.write("\tsignal reset, not_reset, clk: std_logic :='0';\n")

noc_file.write("\n")
noc_file.write("begin\n\n")


noc_file.write("   clk_process :process\n")
noc_file.write("   begin\n")
noc_file.write("        clk <= '0';\n")
noc_file.write("        wait for clk_period/2;   \n")
noc_file.write("        clk <= '1';\n")
noc_file.write("        wait for clk_period/2; \n")
noc_file.write("   end process;\n")
noc_file.write("\n")
noc_file.write("reset <= '1' after 1 ns;\n")

noc_file.write("-- instantiating the network\n")

noc_file.write("-- instantiating the flit trackers\n")
for i in range(0, network_dime**2):
    noc_file.write("F_T_"+str(i)+"_T: flit_tracker  generic map (\n")
    noc_file.write("        DATA_WIDTH => "+str(data_width)+", \n")
    noc_file.write("        tracker_file =>\"traces/track"+str(i)+"_T.txt\"\n")
    noc_file.write("    )\n")
    noc_file.write("    port map (\n")
    noc_file.write("        clk => clk, RX => TX_L_"+str(i)+", \n")
    noc_file.write("        valid_in => valid_out_L_"+str(i)+"\n")
    noc_file.write("    );\n")


string_to_print = ""
string_to_print += "NoC: network_"+str(network_dime)+"x"+str(network_dime)+" generic map (DATA_WIDTH  => "+str(data_width)+", DATA_WIDTH_LV => 11)\n"
string_to_print += "port map (reset, clk, \n"

for i in range(network_dime**2):
    string_to_print += "\tRX_L_"+str(i)+", credit_out_L_"+str(i)+", valid_out_L_"+str(i)+", credit_in_L_"+str(i)+", valid_in_L_"+str(i)+",  TX_L_"+str(i)+", \n"

noc_file.write(string_to_print[:len(string_to_print)-3])
noc_file.write("\n            ); \n")


noc_file.write("not_reset <= not reset; \n")


noc_file.write("\n")
noc_file.write("-- connecting the packet generators\n")
if random_dest or bit_reversal:
  for i in range(0, network_dime*network_dime):
    random_start = random.randint(3, 50)
    if got_finish_time:
      random_end = sim_finish_time
    else:
      random_end = random.randint(random_start, 200)

    noc_file.write("credit_counter_control(clk, credit_out_L_"+str(i)+", valid_in_L_"+str(i)+", credit_counter_out_"+str(i)+");\n")

    if random_dest:
      noc_file.write("gen_random_packet("+str(network_dime)+", "+str(frame_size)+", "+str(i)+", "+str(random_start)+", " +str(packet_size_min)+", " +str(packet_size_max)+", " +
                    str(random_end)+" ns, clk, credit_counter_out_"+str(i)+", valid_in_L_"+str(i)+", RX_L_"+str(i)+");\n")
    elif bit_reversal:
      noc_file.write("gen_bit_reversed_packet("+str(network_dime)+", "+str(frame_size)+", "+str(i)+", "+str(random_start)+", " +str(packet_size_min)+", " +str(packet_size_max)+", " +
                    str(random_end)+" ns, clk, credit_counter_out_"+str(i)+", valid_in_L_"+str(i)+", RX_L_"+str(i)+");\n")
    noc_file.write("\n")


noc_file.write("\n")
noc_file.write("-- connecting the packet receivers\n")
for i in range(0, network_dime*network_dime):
  noc_file.write("get_packet("+str(data_width)+", 5, "+str(i)+", clk, credit_in_L_"+str(i)+", valid_out_L_"+str(i)+", TX_L_"+str(i)+");\n")

noc_file.write("\n\n")

noc_file.write("end;\n")
