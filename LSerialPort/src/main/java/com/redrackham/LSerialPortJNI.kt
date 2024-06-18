package com.redrackham

object LSerialPortJNI {

    init {
        System.loadLibrary("lserialport")
    }

    external fun native_openSerialPort(
        path: String,
        baudrate: Int,
        dataBits: Int,
        parity: Int,
        stopBits: Int,
        checkIntervalWaitMills: Int
    ): Int

    external fun native_hasOpen(path: String): Boolean
    external fun native_sendMsg(path: String, msg: ByteArray?)

    external fun native_setLSerialPortDataListener(
        path: String, listener: LSerialPortDataListener
    )


    external fun native_openSerialPortWriteOnly(
        path: String,
        baudrate: Int,
        dataBits: Int,
        parity: Int,
        stopBits: Int,
    ): Int

    external fun native_openSerialPortReadOnly(
        path: String,
        baudrate: Int,
        dataBits: Int,
        parity: Int,
        stopBits: Int,
        checkIntervalWaitMills: Int
    ): Int

    external fun native_closeSerialPort(
        path: String,
    ): Int


    //---------同步模块相关api--------------
    external fun native_openSyncSerialPort(
        path: String,
        baudrate: Int,
        dataBits: Int,
        parity: Int,
        stopBits: Int,
        readTimeoutMills: Int
    ): Long

    external fun native_syncDataAvailable(device_ptr: Long): Boolean

    external fun native_syncWrite(device_ptr: Long, data: ByteArray?)

    external fun native_syncRead(device_ptr: Long): ByteArray

    external fun native_closeSyncSerialPort(path: String): Int

}