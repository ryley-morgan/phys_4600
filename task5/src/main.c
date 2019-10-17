#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char resultBuffer[256];
    char idnQuery[] = "*IDN?\n";
    char dataSourceQuery[] = "DAT:SOU?\n";
    char setChanOne[] = "DAT:SOU CH1\n";
    char curveQuery[] = "CURV?\n";
    char dataQuery[] = "DAT?\n";
    char ch1ScaleQuery[] = "CH1:SCA?\n";
    char encodeQuery[] = "DATA:ENCDG?\n";
    char widthQuery[] = "DATA:WID?\n";
    ViStatus status = VI_SUCCESS;
    ViFindList resourceList;
    ViUInt32 num_inst;
    ViUInt32 resultCount=0;

    ViSession defaultRM, scopeHandle;
    ViChar description[VI_FIND_BUFLEN];
    ViChar dataBuffer[2500];

    int y;
    float ch1DAC; // Digital to Analog conversion factor
    int data_width;
    float ch1Waveform[2500];

    status = viOpenDefaultRM(&defaultRM);


    if(status == VI_SUCCESS)
    {
        //"USB[0-9]::0?*INSTR"
        //"GPIB[0-9]*::?*INSTR"
        //"USB::0x0699::0x0368::C026271::INSTR"
        //status = viFindRsrc(defaultRM, "USB0::0x0699::0x0368::C026271::INSTR",&resourceList,&num_inst,description);
        status = viFindRsrc(defaultRM, "USB[0-9]::0?*INSTR",&resourceList,&num_inst,description);
        if(status == VI_SUCCESS)
        {   // use "USB0::0x0699::0x0368::C026271::INSTR" instead of description below?
            status = viOpen(defaultRM,description, VI_NULL,VI_NULL,&scopeHandle);
            //ViStatus viGetAttribute(scopeHandle,VI_ATTR_TMO_VALUE, ViAttrState attrState);
            //viGetAttribute(scopeHandle,(ViAttr)"VI_ATTR_TMO_VALUE");
            status = viClear(scopeHandle); //Clear scope IO buffers
            if(status == VI_SUCCESS)
            {
                printf("Opened %s\n",description);
                
              /*viWrite(scopeHandle,idnQuery,(ViUInt32)strlen(idnQuery),&resultCount);
                sleep(2);
                viRead(scopeHandle,resultBuffer,256,&resultCount);
                resultBuffer[resultCount] = 0;
                */
                // Query scope
                

                printf("Result Count = %d\n", resultCount);
                printf("Result Buffer = %s\n", resultBuffer);

                // Set scopeHandle to use channel one of the oscilloscope
                viClear(scopeHandle);
                viWrite(scopeHandle, setChanOne, (ViUInt32)strlen(setChanOne), &resultCount); sleep(2);
                // Check what channel scopeHandle is using
                viWrite(scopeHandle, dataSourceQuery, (ViUInt32)strlen(dataSourceQuery), &resultCount); sleep(2);
                viRead(scopeHandle, resultBuffer, 256, &resultCount);
                resultBuffer[resultCount] = 0;
                printf("Data Source = %s\n",resultBuffer);
                resultBuffer[0]='\0';

                // Check data encoding
                viWrite(scopeHandle, encodeQuery, (ViUInt32)strlen(encodeQuery), &resultCount); sleep(2);
                viRead(scopeHandle, resultBuffer, 256, &resultCount);
                resultBuffer[resultCount] = 0;
                printf("Data Encoding = %s\n",resultBuffer);
                resultBuffer[0]='\0';

                // Check data width
                viWrite(scopeHandle, widthQuery, (ViUInt32)strlen(widthQuery), &resultCount); sleep(2);
                viRead(scopeHandle, resultBuffer, 256, &resultCount);
                sscanf(resultBuffer,"%d",&data_width);
                switch(data_width)
                {
                    case 1:
                        data_width = 256;
                        break;
                    case 2:
                        data_width = 65536;
                        break;
                }
                resultBuffer[0]='\0';
                printf("Data Width = %d\n", data_width);

                //viWrite(scopeHandle, dataSourceQuery,(ViUInt32)strlen(dataSourceQuery),&resultCount);
                //viRead(scopeHandle, resultBuffer, 256,&resultCount);

                // Get voltage scale data from channel 1
                viClear(scopeHandle);
                viWrite(scopeHandle, ch1ScaleQuery, (ViUInt32)strlen(ch1ScaleQuery), &resultCount); sleep(2);
                viRead(scopeHandle,resultBuffer,256,&resultCount);
                sscanf(resultBuffer,"%f", &ch1DAC);
                printf("CH1 Voltage Scale: %f (Volts/Div)\n",ch1DAC);
                ch1DAC = ch1DAC*8/data_width; //Scale for Digital-to-Analog conversion
                printf("CH1 Digital to Analog conversion factor: %f (Volts/adc_step)\n", ch1DAC);
                resultBuffer[0]='\0';

                // Get scope curve
                get_curve(scopeHandle, dataBuffer, 2500);
                
                //printf("[WARN] - READ STATUS: %d",status);
                for (int i = 0; i < 2500; ++i)
                {
                    y = dataBuffer[i];
                    ch1Waveform[i] = y*ch1DAC;
                    printf("Raw = %x,\tRead = %d,\t Value = %f\n",y,y,ch1Waveform[i]);
                }
            }
            else
                printf("Failed to open %s",description);
        }
        else
            printf("Couldn't find any instruments");
    }
    else
        printf("Failed to open defaultRM");
    return 0;
}
