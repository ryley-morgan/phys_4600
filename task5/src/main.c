#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vi_tools.h"

int main(int argc, char const *argv[])
{
    int y, dataSource, dataWidth;
    float ch1DAC, dataEncoding;
    float ch1Waveform[2500];
    char idn[VI_FIND_BUFLEN];

    //ViChar description[VI_FIND_BUFLEN];
    ViChar dataBuffer[DATA_BUFFER_SIZE];
    ViChar resultBuffer[VI_FIND_BUFLEN];

    ViFindList resourceList;

    ViUInt32 numInst;
    ViUInt32 resultCount=0;
    
    ViStatus status = VI_SUCCESS;
    ViSession defaultRM, scopeHandle, FGHandle;

    // Open default remote connection
    status = viOpenDefaultRM(&defaultRM);

    if(status == VI_SUCCESS)
    {
        status = open_scope(&defaultRM,&scopeHandle,&resourceList, &numInst);
        if(status == VI_SUCCESS)
        {
            viSetAttribute(scopeHandle, VI_ATTR_TMO_VALUE, 3000);
            // Get Scope IDN
            get_idn(scopeHandle,&resultBuffer[0],RESULT_BUFFER_SIZE); // From vi_tools.h
            sscanf(resultBuffer,"%s",idn);
            printf("Result Buffer = %s\n",idn);

            // Set scopeHandle to use CH1
            set_channel(scopeHandle, 1);
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_data_source(scopeHandle,&resultBuffer[0],RESULT_BUFFER_SIZE); // Get data source
            printf("Data Source = %s\n",resultBuffer); // Print current data source
            sscanf(resultBuffer,"%i",&dataSource);

            // Check data endoding
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_data_encoding(scopeHandle,&resultBuffer[0],RESULT_BUFFER_SIZE);
            printf("Data Encoding = %s\n",resultBuffer);
            sscanf(resultBuffer,"%e",&dataEncoding);

            // Get channel data width
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_data_width(scopeHandle,&resultBuffer[0],RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%d",&dataWidth);
            switch(dataWidth)      // Convert output from data width to 
            {
                case 1:
                    dataWidth = 256/2;
                    break;
                case 2:
                    dataWidth = 65536/2;
                    break;
            }
            printf("Data Width = %d\n", dataWidth);

            // Get channel 1 voltage scale
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_voltage(scopeHandle,1,&resultBuffer[0],RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%f", &ch1DAC);
            printf("CH1 Voltage Scale: %f (Volts/Div)\n",ch1DAC);
            ch1DAC = ch1DAC*10/dataWidth; //Scale for Digital-to-Analog conversion with 10 full divisions (2 are missing from screen)
            printf("CH1 Digital to Analog conversion factor: %f (Volts/adc_step)\n", ch1DAC);

            // Set data widths to get complete waveform
            set_data_start(scopeHandle);
            set_data_stop(scopeHandle);

            // Get scope curve
            get_curve(scopeHandle, &dataBuffer[0], 2500);
        
            // Convert data using digital to analog conversion factor: ch1DAC
            for (int i = 0; i < 2500; ++i)
            {
                y = dataBuffer[i];
                ch1Waveform[i] = y*ch1DAC;
                printf("Raw = %x,\tRead = %d,\t Value = %f\n",y,y,ch1Waveform[i]);
            }
        }

    }
    else
        printf("Failed to open defaultRM");
    return 0;
}

