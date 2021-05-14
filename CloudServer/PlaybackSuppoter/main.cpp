#pragma once
#include <zmq.hpp>

#include <thread> 
#include <string>

#include "../../service/global_name.hpp"

using namespace std;

int main(int argc, char *argv[]){
    
    // SUB
    zmq::context_t contextSub(1);
    printf("sub context generated (in main)\n");

    while(1)
    {
        // [Wait until there is a request from Ground Station]

    // [Get zip file from local storage]    

    // [Send the zip file to Ground Station]
    }
    

}