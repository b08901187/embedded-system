/* Sockets Example
 * Copyright (c) 2016-2020 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "wifi_helper.h"
#include "mbed-trace/mbed_trace.h"

#include "stm32l475e_iot01_tsensor.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_accelero.h"
#include <cstdint>

#if MBED_CONF_APP_USE_TLS_SOCKET
#include "root_ca_cert.h"


#ifndef DEVICE_TRNG
#error "mbed-os-example-tls-socket requires a device which supports TRNG"
#endif
#endif // MBED_CONF_APP_USE_TLS_SOCKET

class SocketDemo {
    static constexpr size_t MAX_NUMBER_OF_ACCESS_POINTS = 20;
    static constexpr size_t MAX_MESSAGE_RECEIVED_LENGTH = 100;

#if MBED_CONF_APP_USE_TLS_SOCKET
    static constexpr size_t REMOTE_PORT = 5420; // tls port
#else
    static constexpr size_t REMOTE_PORT = 5420; // standard HTTP port
#endif // MBED_CONF_APP_USE_TLS_SOCKET

public:
    SocketDemo() : _net(NetworkInterface::get_default_instance())
    {
    }

    ~SocketDemo()
    {
        if (_net) {
            _net->disconnect();
        }
    }

    void run()
    {
        if (!_net) {
            printf("Error! No network interface found.\r\n");
            return;
        }

        /* if we're using a wifi interface run a quick scan */
        if (_net->wifiInterface()) {
            /* the scan is not required to connect and only serves to show visible access points */
            wifi_scan();

            /* in this example we use credentials configured at compile time which are used by
             * NetworkInterface::connect() but it's possible to do this at runtime by using the
             * WiFiInterface::connect() which takes these parameters as arguments */
        }

        /* connect will perform the action appropriate to the interface type to connect to the network */

        printf("Connecting to the network...\r\n");

        nsapi_size_or_error_t result = _net->connect();
        if (result != 0) {
            printf("Error! _net->connect() returned: %d\r\n", result);
            return;
        }

        print_network_info();

        /* opening the socket only allocates resources */
        result = _socket.open(_net);
        if (result != 0) {
            printf("Error! _socket.open() returned: %d\r\n", result);
            return;
        }

#if MBED_CONF_APP_USE_TLS_SOCKET
        result = _socket.set_root_ca_cert(root_ca_cert);
        if (result != NSAPI_ERROR_OK) {
            printf("Error: _socket.set_root_ca_cert() returned %d\n", result);
            return;
        }
        _socket.set_hostname(MBED_CONF_APP_HOSTNAME);
#endif // MBED_CONF_APP_USE_TLS_SOCKET

        /* now we have to find where to connect */

        SocketAddress address = SocketAddress("192.168.109.158",5420);

        /*if (!resolve_hostname(address)) {
            return;
        }*/

        //address.set_port(REMOTE_PORT);

        /* we are connected to the network but since we're using a connection oriented
         * protocol we still need to open a connection on the socket */

        printf("Opening connection to remote port %d\r\n", REMOTE_PORT);

        result = _socket.connect(address);
        if (result != 0) {
            printf("Error! _socket.connect() returned: %d\r\n", result);
            return;
        }
        sensor_BSP();
        /* exchange an HTTP request and response */

        /*if (!send_http_request()) {
            return;
        }

        if (!receive_http_response()) {
            return;
        }*/

        printf("Demo concluded successfully \r\n");
    }

private:
    bool resolve_hostname(SocketAddress &address)
    {
        const char hostname[] = MBED_CONF_APP_HOSTNAME;

        /* get the host address */
        printf("\nResolve hostname %s\r\n", hostname);
        nsapi_size_or_error_t result = _net->gethostbyname(hostname, &address);
        if (result != 0) {
            printf("Error! gethostbyname(%s) returned: %d\r\n", hostname, result);
            return false;
        }

        printf("%s address is %s\r\n", hostname, (address.get_ip_address() ? address.get_ip_address() : "None") );

        return true;
    }

    bool sensor_BSP()
    {
    float sensor_value = 0;
    int16_t MApDataXYZ[3] = {0};
    int16_t pDataXYZ[3] = {0};
    float pGyroDataXYZ[3] = {0};

    printf("Start sensor init\n");

    DigitalOut led(LED1);
    BSP_TSENSOR_Init();
    BSP_HSENSOR_Init();
    BSP_PSENSOR_Init();

    BSP_MAGNETO_Init();
    BSP_GYRO_Init();
    BSP_ACCELERO_Init();
    int sample_num = 0;
    char temp_json[1000] ;
    char hum_json[1000] ;
    char pre_json[1000] ;
    char acc_json[1000] ;
    char gyro_json[1000] ;
    char mag_json[1000] ;
    int SCALE_MULTIPLIER = 1;

    while(1) {
        printf("\nNew loop, LED1 should blink during sensor read\n");

        led = 1;
        ++sample_num;
        BSP_MAGNETO_GetXYZ(MApDataXYZ);
        BSP_GYRO_GetXYZ(pGyroDataXYZ);
        BSP_ACCELERO_AccGetXYZ(pDataXYZ);
        
        int16_t MAx = MApDataXYZ[0], MAy = MApDataXYZ[1], MAz = MApDataXYZ[2];
        int16_t ACx = pDataXYZ[0], ACy = pDataXYZ[1], ACz = pDataXYZ[2];
        float GYx = pGyroDataXYZ[0], GYy = pGyroDataXYZ[1], GYz = pGyroDataXYZ[2];


        float sensor_value_temp = BSP_TSENSOR_ReadTemp();
        printf("\nTEMPERATURE = %.2f degC\n", sensor_value_temp);
        /*int temp_len = sprintf(temp_json,"{\"temperature\":%f,\"s\":%d}",(float)((int)(sensor_value_temp*10000))/10000, sample_num);
        int response1 = _socket.send(temp_json,temp_len);
        if (0 >= response1){
            printf("Error seding: %d\n", response1);
        }*/

        float sensor_value_hum = BSP_HSENSOR_ReadHumidity();
        printf("HUMIDITY = %.2f %%\n", sensor_value_hum);
        /*int hum_len = sprintf(hum_json,"{\"HUMIDITY\":%f,\"s\":%d}",(float)((int)(sensor_value_hum*10000))/10000, sample_num);
        int response2 = _socket.send(hum_json,hum_len);
        if (0 >= response2){
            printf("Error seding: %d\n", response2);
        }*/

        //ThisThread::sleep_for(500);

        float sensor_value_pre = BSP_PSENSOR_ReadPressure();
        printf("PRESSURE is = %.2f mBar\n", sensor_value_pre);
        /*int pre_len = sprintf(pre_json,"{\"Pressure\":%f,\"s\":%d}",(float)((int)(sensor_value_pre*10000))/10000, sample_num);
        int response3 = _socket.send(pre_json,pre_len);
        if (0 >= response3){
            printf("Error seding: %d\n", response3);
        }*/
        
        //ThisThread::sleep_for(500);
        //ThisThread::sleep_for(1000);

        printf("\nMAGNETO_X = %d\n", MApDataXYZ[0]);
        printf("MAGNETO_Y = %d\n", MApDataXYZ[1]);
        printf("MAGNETO_Z = %d\n", MApDataXYZ[2]);
        int mag_len = sprintf(mag_json,"{\"MAGNETO_x\":%f,\"MAGNETO_y\":%f,\"MAGNETO_z\":%f,\"s\":%d}",(float)((int)(MAx*10000))/10000,(float)((int)(MAy*10000))/10000, (float)((int)(MAz*10000))/10000, sample_num);
        int response4 = _socket.send(mag_json,mag_len);
        if (0 >= response4){
            printf("Error seding: %d\n", response4);
        }
        ThisThread::sleep_for(500);

        printf("\nGYRO_X = %.2f\n", pGyroDataXYZ[0]);
        printf("GYRO_Y = %.2f\n", pGyroDataXYZ[1]);
        printf("GYRO_Z = %.2f\n", pGyroDataXYZ[2]);
        int gyro_len = sprintf(gyro_json,"{\"GYRO_x\":%f,\"GYRO_y\":%f,\"GYRO_z\":%f,\"s\":%d}",(float)((int)(GYx*10000))/10000,(float)((int)(GYy*10000))/10000, (float)((int)(GYz*10000))/10000, sample_num);
        int response5 = _socket.send(gyro_json,gyro_len);
        if (0 >= response5){
            printf("Error seding: %d\n", response5);
        }     
        ThisThread::sleep_for(500);

        printf("\nACCELERO_X = %d\n", pDataXYZ[0]);
        printf("ACCELERO_Y = %d\n", pDataXYZ[1]);
        printf("ACCELERO_Z = %d\n", pDataXYZ[2]);
        int acc_len = sprintf(acc_json,"{\"ACCELERO_x\":%f,\"ACCELERO_y\":%f,\"ACCELERO_z\":%f,\"s\":%d}",(float)((int)(ACx*10000))/10000,(float)((int)(ACy*10000))/10000, (float)((int)(ACz*10000))/10000, sample_num);
        int response6 = _socket.send(acc_json,acc_len);
        if (0 >= response6){
            printf("Error seding: %d\n", response6);
        }           

        
        led = 0;

        ThisThread::sleep_for(500);

    }

}

    /*bool send_http_request()
    {
        // loop until whole request sent 
        const char buffer[] = "GET / HTTP/1.1\r\n"
                              "Host: ifconfig.io\r\n"
                              "Connection: close\r\n"
                              "\r\n";

        nsapi_size_t bytes_to_send = strlen(buffer);
        nsapi_size_or_error_t bytes_sent = 0;

        printf("\r\nSending message: \r\n%s", buffer);

        while (bytes_to_send) {
            bytes_sent = _socket.send(buffer + bytes_sent, bytes_to_send);
            if (bytes_sent < 0) {
                printf("Error! _socket.send() returned: %d\r\n", bytes_sent);
                return false;
            } else {
                printf("sent %d bytes\r\n", bytes_sent);
            }

            bytes_to_send -= bytes_sent;
        }

        printf("Complete message sent\r\n");

        return true;
    }

    bool receive_http_response()
    {
        char buffer[MAX_MESSAGE_RECEIVED_LENGTH];
        int remaining_bytes = MAX_MESSAGE_RECEIVED_LENGTH;
        int received_bytes = 0;

        // loop until there is nothing received or we've ran out of buffer space 
        nsapi_size_or_error_t result = remaining_bytes;
        while (result > 0 && remaining_bytes > 0) {
            result = _socket.recv(buffer + received_bytes, remaining_bytes);
            if (result < 0) {
                printf("Error! _socket.recv() returned: %d\r\n", result);
                return false;
            }

            received_bytes += result;
            remaining_bytes -= result;
        }

        // the message is likely larger but we only want the HTTP response code 

        printf("received %d bytes:\r\n%.*s\r\n\r\n", received_bytes, strstr(buffer, "\n") - buffer, buffer);

        return true;
    }*/

    void wifi_scan()
    {
        WiFiInterface *wifi = _net->wifiInterface();

        WiFiAccessPoint ap[MAX_NUMBER_OF_ACCESS_POINTS];

        /* scan call returns number of access points found */
        int result = wifi->scan(ap, MAX_NUMBER_OF_ACCESS_POINTS);

        if (result <= 0) {
            printf("WiFiInterface::scan() failed with return value: %d\r\n", result);
            return;
        }

        printf("%d networks available:\r\n", result);

        for (int i = 0; i < result; i++) {
            printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\r\n",
                   ap[i].get_ssid(), get_security_string(ap[i].get_security()),
                   ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
                   ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5],
                   ap[i].get_rssi(), ap[i].get_channel());
        }
        printf("\r\n");
    }

    void print_network_info()
    {
        /* print the network info */
        SocketAddress a;
        _net->get_ip_address(&a);
        printf("IP address: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
        _net->get_netmask(&a);
        printf("Netmask: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
        _net->get_gateway(&a);
        printf("Gateway: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
    }

private:
    NetworkInterface *_net;

#if MBED_CONF_APP_USE_TLS_SOCKET
    TLSSocket _socket;
#else
    TCPSocket _socket;
#endif // MBED_CONF_APP_USE_TLS_SOCKET
};

int main() {
    printf("\r\nStarting socket demo\r\n\r\n");

#ifdef MBED_CONF_MBED_TRACE_ENABLE
    mbed_trace_init();
#endif

    SocketDemo *example = new SocketDemo();
    MBED_ASSERT(example);
    example->run();

    return 0;
}
