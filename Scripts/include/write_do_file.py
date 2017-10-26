
import file_lists
from Scripts.include.package import *
from math import ceil

def include_cmd(path):
    if path.endswith(('.vhd', '.vhdl')):
        return 'vcom'
    return 'vlog'

def write_do_file(program_argv, net_file_name, net_tb_file_name, wave_do_file_name, logging):
    """
    Generates a simulate.do file for running Modelsim.
        program_argv:       program arguments
        net_file_name:      file name for the generated network
        net_tb_file_name:   file name for the generated network
        wave_do_file_name:  file name for the generated wave.do file
        logging:            logging file
    """

    logging.info("Generating simulation.do")

    do_file = open(SIMUL_DIR + "/" + SIMUL_DO_SCRIPT, 'w')

    do_file.write("#########################################\n")
    do_file.write("# Copyright (C) 2016 Project Bonfire    #\n")
    do_file.write("#                                       #\n")
    do_file.write("# This file is automatically generated! #\n")
    do_file.write("#             DO NOT EDIT!              #\n")
    do_file.write("#########################################\n\n")

    do_file.write("vlib work\n\n")

    do_file.write("# Include files and compile them\n")

    if program_argv['vc']:
        do_file.write("vcom \"" + TEST_DIR  \
                      + "/router_pack_vc.vhd"+"\"\n")
        List_of_files = file_lists.vc_files
        for file in List_of_files:
            do_file.write(include_cmd(file) + " \"" + ROUTER_VC_RTL_DIR +file+"\"\n")
        do_file.write("vcom \"" + ROUTER_VC_RTL_DIR + "/Router_32_bit_credit_based.vhd\"\n")

        do_file.write("vcom \"" + TEST_DIR \
                      + "/TB_Package_32_bit_" + CREDIT_BASED_SUFFIX + "_vc.vhd\"\n")
    else:
        do_file.write("vcom \"" + TEST_DIR  \
                      + "/router_pack.vhd"+"\"\n")
        List_of_files = file_lists.credit_based_files
        for file in List_of_files:
            do_file.write(include_cmd(file) + " \"" + ROUTER_RTL_DIR +file+"\"\n")

        do_file.write("vcom \"" + ROUTER_RTL_DIR + "/Router_32_bit_credit_based.vhd\"\n")

        do_file.write("vcom \"" + TEST_DIR \
                      + "/TB_Package_32_bit_" + CREDIT_BASED_SUFFIX + ".vhd\"\n")

    if program_argv['trace'] :
        do_file.write("vcom \"" + ROUTER_RTL_DIR + "flit_tracker.vhd\"\n")

    # Generated network files
    do_file.write("vcom \"" +  net_file_name + "\"\n")
    do_file.write("vcom \"" +  net_tb_file_name + "\"\n\n")

    #### Simulation control ####

    do_file.write("# Start the simulation\n")
    do_file.write("vsim work.tb_network_" \
        + str(program_argv['network_dime']) + "x" + str(program_argv['network_dime']) + "\n\n")

    do_file.write("# Draw waves\n")
    do_file.write("do " + wave_do_file_name + "\n")

    do_file.write("# Run the simulation\n")
    do_file.write("vcd file wave.vcd\n")
    do_file.write("vcd add -r -optcells /*\n")


    do_file.write("run " + str(program_argv['end']) + " ns\n")

    do_file.write("vcd flush\n")

    if program_argv['command-line'] or program_argv['lat']:
        do_file.write("\n# Exit Modelsim after simulation\n")
        do_file.write("exit\n")
    do_file.close()
    logging.info("finished writing do file...")

    return None
