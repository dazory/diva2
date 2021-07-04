/*
 * main.cpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#include <iostream>
#include <stdexcept>

#include <fstream>
#include <string>
using namespace std;

#include "header/dbciterator.hpp"

const std::string usage = ""
		"This parser is meant to be used via CLI at the moment\n"
		"	./parser <FILE>\n"
		"	\n"
		"example:\n"
		"	./candbcparser /home/diva2/dbc/Vehicle_CAN_GEN2_v2.6_EV_CAN1.dbc\n";

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << usage << std::endl;
		return 0;
	}

    ofstream wFile;
    wFile.open("dbc2.txt");

	try {
		DBCIterator dbc(argv[1]);
        for(auto message : dbc) {
            // std::cout << message.getName() << " " << message.getId() << std::endl;
            char cBuff[1000];
            printf("BO_ %d %s: %d\n", message.getId(), message.getName().c_str(), message.getDlc());
            int n = sprintf(cBuff, "BO_ %d %s: %d\n", message.getId(), message.getName().c_str(), message.getDlc());
            wFile.write(cBuff, n);
            for(auto sig : message) {
                /*
                Signal syntax		: SG_
                Name			: N
                Bit start | length	: 16|16
                Little endian(unsigned)	: @1+
                (scale, offset)		: (0.25, 0)
                [min | max]		: [0 | 16383.8]
                "unit"			: "rpm"
                Receiver		: XXX
                */
                // std::cout << "    SG_ " << sig.getName() << "  ";
                // std::cout << "To: ";
                
                // <Signal syntax Name : >
                printf("    SG_ %s : ", sig.getName().c_str());
                n = sprintf(cBuff, "    SG_ %s : ", sig.getName().c_str());
                wFile.write(cBuff, n);
                
                // <Bit start | length >
                // std::cout << sig.getStartbit() << "," << sig.getLength() << std::endl;
                printf("%d|%d", sig.getStartbit(), sig.getLength());
                n = sprintf(cBuff, "%d|%d", sig.getStartbit(), sig.getLength());
                wFile.write(cBuff, n);

                // <Little endian(unsigned)>
                printf(" %d+ ", sig.getSign());
                n = sprintf(cBuff, " %d+ ", sig.getSign());
                wFile.write(cBuff, n);
                
                // <(scale, offset)>
                printf("(%f, %f) ", sig.getFactor(), sig.getOffset());
                n = sprintf(cBuff, "(%f, %f) ", sig.getFactor(), sig.getOffset());
                wFile.write(cBuff, n);
                
                // <[min|max]>
                printf("(%f, %f) ", sig.getMinimum(), sig.getMaximum());
                n = sprintf(cBuff, "(%f, %f) ", sig.getMinimum(), sig.getMaximum());
                wFile.write(cBuff, n);
                
                // <"unit">
                printf("\"%s\" ", sig.getUnit().c_str());
                n = sprintf(cBuff, "\"%s\" ", sig.getUnit().c_str());
                wFile.write(cBuff, n);
                
                // <Receiver>
                for (auto to : sig.getTo()) {
                    std::cout << to << ", ";
                    wFile.write(to.c_str(), to.size());
                    wFile.write(" ",1);
                }
                printf("\n");
                wFile.write("\n\n", 2);
                
                /*
                std::cout << "(" << sig.getFactor() << ", " << sig.getOffset() << ")" << std::endl;
                n = sprintf(cBuff, "(%f, %f)\n", sig.getFactor(), sig.getOffset());
                wFile.write(cBuff, n);
                std::cout << "[" << sig.getMinimum() << "," << sig.getMaximum() << "]" << std::endl;
                n = sprintf(cBuff, "[%f, %f]\n", sig.getMinimum(), sig.getMaximum());
                wFile.write(cBuff, n);
                if (sig.getMultiplexor() == Multiplexor::MULTIPLEXED) {
                    std::cout << "#" << sig.getMultiplexedNumber() << "#" << std::endl;
                    n = sprintf(cBuff, "#%d#\n", sig.getMultiplexedNumber());
                    wFile.write(cBuff, n);
                
                } else if (sig.getMultiplexor() == Multiplexor::MULTIPLEXOR) {
                    std::cout << "+Multiplexor+" << std::endl;
                    wFile.write("+Multiplexor", 10);
                }
                */

                // std::cout << std::endl;
            };
        }

	} catch (std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}

    wFile.clear();

//	return 0;
}
