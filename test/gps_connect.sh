### diva2/test/sensor_connection/gps_connect.sh
#!/bin/bash

echo "Setting GPS"
sudo chmod 777 /dev/ttyACM0

sudo echo -e n'\xB5\x62\x06\x08\x06\x00\x64\x00\x01\x00\x01\x00\x7A\x12\xB5\x62\x06\x08\x00\x00\x0E\x30' > /dev/ttyACM0

# cd Documents
echo "Logging GPS..."
#g++ -o gps_connect sensor_connect/gps_connect.cpp
#./gps_connect /dev/ttyACM0 9600
cd ..
cd build/test/sensor_connect
./sensor_connect /dev/ttyACM0 9600
echo "Connect Complete!"

#g++ -o gps_parsing sensor_parsing/gps_parsing.cpp -lpthread
#./gps_parsing
cd ..
cd sensor_parsing
./sensor_parsing
echo "Parsing Complete!"