from Scripts.include.helper_func import *


def print_help(argv, program_argv):
    """
    Gets the program arguments and prints manual for the program.
    """
    print BOLD + "Usage:" + ENDC
    print
    print BOLD + OKBLUE + "  Network parameters:" + ENDC
    print
    print BOLD + "  -D [size]:" + ENDC
    print "\tMake a network of [size]X[size]. Size can be only multiples of two. " \
        + "Default value is " + str(program_argv['network_dime']) + "."
    print
    print BOLD + OKBLUE + "  Simulation parameters:" + ENDC
    print BOLD + "  -Rand [PIR]:" + ENDC
    print "\tUse Random traffic pattern generator with packet injection rate equal to PIR (value between 0 and 1)."
    print "\t\t**Cannot be used togeter with -BR.**"
    print "\t\tIf neither -Rand or -BR is specified, system defaults to repeatative packets being sent from source to same destination."
    print
    print BOLD + "  -BR [PIR]:" + ENDC
    print "\tUse Bit Reversal traffic pattern generator with packet injection rate equal to PIR (value between 0 and 1)."
    print "\t\t**Cannot be used togeter with -Rand.**"
    print "\t\tIf neither -Rand or -BR is specified, system defaults to repeatative packets being sent from source to same destination."
    print
    print BOLD + "  -PS [min] [max]:" + ENDC
    print "\tSpecify packet size range. Default min value is 3 and defualt max value is 8."
    print
    print BOLD + "  -sim [sim_time]:" + ENDC
    print "\tSpecifies the length of simulation in clock cycles. which at this time the packet generators will stop sending packets."
    print
    print BOLD + "  -end [end_time]:" + ENDC
    print "\tSpecifies the length of simulation in nanoseconds. After this time the simulation will be stopped, even if the packet injection is still active."
    print "\tIf this parameter is not specified, but -sim is specified, the default value is 1.5*sim."
    print "\tIf this parameter is not specified and -sim is also not specified, it defaults to 15000 ns."
    print
    print BOLD + "  -lat:" + ENDC
    print "\tCalculate the average packet latency (in terms of clock cycles). Disables Modelsim GUI."
    print
    print
    print BOLD + OKBLUE + "  Other parameters:" + ENDC
    print BOLD + "  --debug:" + ENDC
    print "\tIncrease verbocity of the script. Useful for debugging."
    print BOLD + "  --trace:" + ENDC
    print "\tadds packet tracing."
    print
    print
    print BOLD + OKBLUE + "  Examples:" + ENDC
    print BOLD + "  Example 1:" + ENDC
    print BOLD + "  Example 2:" + ENDC
   
