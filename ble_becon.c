#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLE_TAG_ADDRESS "47894F4F4B534F4349414C4449535445"  // Replace with your BLE beacon address

void accelometer_check(const char *data) {
    // Assuming the accelerometer data is at a specific offset in the advertisement packet
    // Modify this based on the actual format of your BLE beacon's data
    int16_t accel_x, accel_y, accel_z;//tydef int to 16bit 
    
    // Example taking accelerometer data is in the format you provided
    sscanf(data + 28, "%4hx%4hx%4hx", &accel_x, &accel_y, &accel_z);
    // Define thresholds for movement detection
    int threshold_x = 100;
    int threshold_y = 100;
    int threshold_z = 100;

    // Check if the device is moving
    if (abs(accel_x) >threshold_x || abs(accel_y) > threshold_y || abs(accel_z) > threshold_z) {
        printf("Tag is moving\n");
    } else {
        printf("Tag is stationary\n");
    }
}

 void battery_volt(const char *a)
   {
    int v;
    sscanf(a+26,"%2x",&v);//takin baterry data 
   printf("battery volt :%d \n",v);// dispalying b.level in deccimal
   }
void mac_addr(const char *m)
{
   char mac[12];
sscanf(m+40,"%s",mac);//extract mac addr from data given
printf("mac_addr :%s\n",mac);//diplaying
} 

int main() {
    // Replace 'XX:XX:XX:XX:XX:XX' with the actual BLE beacon address
    const char *ble_tag_address = "53594F4F4B534F4349414C4449535445";
      const char *raw_data[] = {
        "0201060303E1FF1216E1FFA10364FFF4000FFF003772A33F23AC",
        "0201060303E1FF1216E1FFA10354FFF60011FF003772A44F23BD",
        "0201060303E1FF1216E1FFA10344FFF40011FF033772A33F23EE"};
   

    for (int i= 0;i<sizeof(raw_data)/sizeof(raw_data[0]);i++)
       {
           accelometer_check(raw_data[i]);
             battery_volt(raw_data[i]);
             mac_addr(raw_data[i]);
  }

    return 0;
}
