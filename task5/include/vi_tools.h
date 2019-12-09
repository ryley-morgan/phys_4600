#ifndef __VI_TOOLS_HEADER__  // Include guard!
#define __VI_TOOLS_HEADER__  // Define vi_tools.h

/*
    Open connection to oscilloscope
    ARGS:
        ViSession defaultRM:            default VISA connection manager
        ViSession *handle:              oscilloscope handle
        ViFindList *resourceList:       resources available for access
        ViUInt32 *numInst:              number of instruments found
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus open_scope(ViSession defaultRM, ViSession *handle, ViFindList *resourceList, ViUInt32 *numInst);

/*
    Retrieve current waveform from oscilloscope
    ARGS:
        ViSession handle:               oscilloscope handle
        ViInt8 *dataBuf:                address of dataBuffer to store retrieved waveform
        ViUInt32 npoints:               number of points to collect for waveform
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_curve(ViSession handle, ViInt8 *dataBuf, ViUInt32 npoints);

/*
    Retrieve current y-axis specification data
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data(ViSession handle, ViChar *resultBuf, int bufferSize);

/*
    Retrieve current y-axis data encoding type e.g. RPBINARY, RIBINARY, etc.
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data_encoding(ViSession handle, ViChar *resultBuf, int bufferSize);

/*
    Retrieve current y-axis number of ADC bin (256-bit or 65535-bit)
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data_width(ViSession handle, ViChar *resultBuf, int bufferSize);

/*
    Retrieve current y-axis data source channel
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data_source(ViSession handle, ViChar *resultBuf, int bufferSize);

/*
    Retrieve current x-axis scale/div in units of volts/div
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_x_scale(ViSession handle, ViChar *resultBuf, int bufferSize);

/*
    Get oscilloscope identification string
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_idn(ViSession handle, ViChar *resultBuf, int bufferSize);

/*
    Retrieve current y-axis voltage/division
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    channel of scope to query
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_voltage(ViSession handle, int channel, ViChar *resultBuf, int bufferSize);

/*
    Set oscilloscope channel to 1,2, or 3(MATH)
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
    OUTPUT:
        Void:
*/
void set_channel(ViSession handle, int channel);

/*
    Set data starting point to default for collecting waveform (0 is the left most point)
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
    OUTPUT:
        Void:
*/
void set_data_start(ViSession handle);

/*
    Set data stop point to default for collecting waveform (2500 is the right most point)
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
    OUTPUT:
        Void:
*/
void set_data_stop(ViSession handle);

/*
    Set oscilloscope voltage scale for channel
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
        float volts:                    floating-point voltage scale
    OUTPUT:
        Void:
*/
void set_voltage(ViSession handle, int channel, float volts);

#endif // End of Include-guard