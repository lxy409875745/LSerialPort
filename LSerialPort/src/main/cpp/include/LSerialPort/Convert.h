#ifndef LSERIALPORT_CONVERT_H
#define LSERIALPORT_CONVERT_H

#include "string"
#include "iostream"
#include "../CppLinuxSerial/SerialPort.h"
#include "../Android/AndroidLog.h"


using namespace mn::CppLinuxSerial;
namespace LSerialPort {


    /**
     * jbyteArray转vector<uint8_t>
     * @param env
     * @param bytearray
     * @return
     */
    inline std::vector<uint8_t>
    convertJByteArrayToVectorU8(JNIEnv * env, jbyteArray & jbytearray) {
        std::vector<uint8_t> vec;
        jbyte *jBytes = env->GetByteArrayElements(jbytearray, nullptr);
        jsize length = env->GetArrayLength(jbytearray);
        vec = std::vector<uint8_t>(reinterpret_cast<uint8_t *>(jBytes),
                                   reinterpret_cast<uint8_t *>(jBytes) + length);
        env->ReleaseByteArrayElements(jbytearray, jBytes, JNI_ABORT);
        return vec;
    }

    /**
     * 软件流控转换
     * @param softwareFlowControl
     * @return
     */
    inline SoftwareFlowControl convertSoftwareFlowControl(const int &softwareFlowControl) {
        SoftwareFlowControl swfc;
        switch (softwareFlowControl) {
            case 0: {
                swfc = SoftwareFlowControl::OFF;
                break;
            }
            case 1: {
                swfc = SoftwareFlowControl::ON;
                break;
            }
            default: {
                THROW_EXCEPT("HardwareFlowControl value not supported!");
            }
        }
        return swfc;
    }


    /**
     * 硬件流控转换
     * @param hardwareFlowControl
     * @return
     */
    inline HardwareFlowControl convertHardwareFlowControl(const int &hardwareFlowControl) {
        HardwareFlowControl hwfc;
        switch (hardwareFlowControl) {
            case 0: {
                hwfc = HardwareFlowControl::OFF;
                break;
            }
            case 1: {
                hwfc = HardwareFlowControl::ON;
                break;
            }
            default: {
                THROW_EXCEPT("HardwareFlowControl value not supported!");
            }
        }
        return hwfc;
    }


    /**
     * 停止位转换
     * @param stopBits
     * @return
     */
    inline NumStopBits convertStopBits(const int &stopBits) {
        NumStopBits sb;
        switch (stopBits) {
            case 1: {
                sb = NumStopBits::ONE;
                break;
            }
            case 2: {
                sb = NumStopBits::TWO;
                break;
            }
            default: {
                THROW_EXCEPT("StopBits value not supported!");
            }
        }
        return sb;
    }


    /**
     * 校验位转换
     * @param parity 0:无校验位(NONE，默认)；1:奇校验位(ODD);2:偶校验位(EVEN)
     * @return
     */
    inline Parity convertParity(const int &parity) {

        Parity p;

        switch (parity) {
            case 0: {
                p = Parity::NONE;
                break;
            }
            case 1: {
                p = Parity::ODD;
                break;
            }
            case 2: {
                p = Parity::EVEN;
                break;
            }
            default: {
                THROW_EXCEPT("Parity value not supported!");
            }
        }
        return p;
    }


    /**
     * 数据位
     * @param dataBits 数据位 5-8
     * @return
     */
    inline NumDataBits convertDataBits(const int &dataBits) {
        NumDataBits db;
        switch (dataBits) {
            case 5: {
                db = NumDataBits::FIVE;
                break;
            }
            case 6: {
                db = NumDataBits::SIX;
                break;
            }
            case 7: {
                db = NumDataBits::SEVEN;
                break;
            }
            case 8: {
                db = NumDataBits::EIGHT;
                break;
            }
            default: {
                THROW_EXCEPT("DataBits value not supported!");
            }
        }
        return db;
    }


}

#endif //LSERIALPORT_CONVERT_H
