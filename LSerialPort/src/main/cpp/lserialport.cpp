#include <jni.h>
#include <string>
#include "iostream"
#include "include/LSerialPort/LSerialPortManager.h"
#include "include/LSerialPort/Convert.h"

using namespace LSerialPort;

//串口管理操作
static std::unique_ptr<LSerialPort::LSerialPortManager> mLSerialPortManager;

//初始化jvm
JavaVM *LSerialPortManager::jvm = nullptr;

// JNI_OnLoad函数实现
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    //赋值jvm
    mLSerialPortManager->jvm = vm;
    auto manager_ptr = std::make_unique<LSerialPortManager>();
    mLSerialPortManager = std::move(manager_ptr);

    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        std::__throw_runtime_error("Get java env failed!");
    }
    //一定要返回版本号，否则会出错。
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_redrackham_LSerialPortJNI_native_1openSyncSerialPort(JNIEnv *env, jobject thiz,
                                                              jstring path, jint baudrate,
                                                              jint data_bits, jint parity,
                                                              jint stop_bits,
                                                              jint hardware_flow_control,
                                                              jint software_flow_control,
                                                              jint read_timeout_mills) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);
    int br = baudrate;
    NumDataBits db = convertDataBits(data_bits);
    Parity p = convertParity(parity);
    NumStopBits sb = convertStopBits(stop_bits);
    HardwareFlowControl hwfc = convertHardwareFlowControl(hardware_flow_control);
    SoftwareFlowControl swfc = convertSoftwareFlowControl(software_flow_control);
    //jint转int32_t
    auto rtm_32 = static_cast<int32_t>(read_timeout_mills);
    long worker_ptr_jlong = mLSerialPortManager->buildSyncReadWriteDevice(path_str, br, db, p, sb,
                                                                          hwfc, swfc,
                                                                          rtm_32);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);
    return worker_ptr_jlong;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_redrackham_LSerialPortJNI_native_1openSerialPortWriteOnly(JNIEnv *env, jobject thiz,
                                                                   jstring path, jint baudrate,
                                                                   jint data_bits, jint parity,
                                                                   jint stop_bits,
                                                                   jint hardware_flow_control,
                                                                   jint software_flow_control) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);
    int br = baudrate;
    NumDataBits db = convertDataBits(data_bits);
    Parity p = convertParity(parity);
    NumStopBits sb = convertStopBits(stop_bits);
    HardwareFlowControl hwfc = convertHardwareFlowControl(hardware_flow_control);
    SoftwareFlowControl swfc = convertSoftwareFlowControl(software_flow_control);
    //这里read_interval_timeout_mills设置为0，因为使用独立线程去检查。不需要配置等待时间了
    int32_t rtm_32 = 0;
    int result = mLSerialPortManager->addWriteOnlyDevice(path_str, br, db, p, sb, hwfc, swfc,
                                                         rtm_32);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);
    return result;
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_redrackham_LSerialPortJNI_native_1openSerialPortReadOnly(JNIEnv *env, jobject thiz,
                                                                  jstring path, jint baudrate,
                                                                  jint data_bits, jint parity,
                                                                  jint stop_bits,
                                                                  jint hardware_flow_control,
                                                                  jint software_flow_control,
                                                                  jint check_interval_wait_mills) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);
    int br = baudrate;
    NumDataBits db = convertDataBits(data_bits);
    Parity p = convertParity(parity);
    NumStopBits sb = convertStopBits(stop_bits);
    HardwareFlowControl hwfc = convertHardwareFlowControl(hardware_flow_control);
    SoftwareFlowControl swfc = convertSoftwareFlowControl(software_flow_control);
    //这里read_interval_timeout_mills设置为0，因为使用独立线程去检查。不需要配置等待时间了
    int32_t rtm_32 = 0;

    //jlong转为long
    long ctm_l = static_cast<long>(check_interval_wait_mills);
    int result = mLSerialPortManager->addReadOnlyDevice(path_str, br, db, p, sb, hwfc, swfc, rtm_32,
                                                        ctm_l);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);
    return result;
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_redrackham_LSerialPortJNI_native_1openSerialPort(JNIEnv *env, jobject thiz, jstring path,
                                                          jint baudrate, jint data_bits,
                                                          jint parity, jint stop_bits,
                                                          jint hardware_flow_control,
                                                          jint software_flow_control,
                                                          jint check_interval_wait_mills) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);
    int br = baudrate;
    NumDataBits db = convertDataBits(data_bits);
    Parity p = convertParity(parity);
    NumStopBits sb = convertStopBits(stop_bits);
    HardwareFlowControl hwfc = convertHardwareFlowControl(hardware_flow_control);
    SoftwareFlowControl swfc = convertSoftwareFlowControl(software_flow_control);
    //这里read_interval_timeout_mills设置为0，因为使用独立线程去检查。不需要配置等待时间了
    int32_t rtm_32 = 0;

    //jlong转为long
    long ctm_l = static_cast<long>(check_interval_wait_mills);
    int result = mLSerialPortManager->addDevice(path_str, br, db, p, sb, hwfc, swfc, rtm_32, ctm_l);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);
    return result;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_redrackham_LSerialPortJNI_native_1sendMsg(JNIEnv *env, jobject thiz, jstring path,
                                                   jbyteArray msg) {
    if (msg == nullptr) {
        return;
    }
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    std::vector<uint8_t> msg_vec = convertJByteArrayToVectorU8(env, msg);
    mLSerialPortManager->sendMessage(path_char, msg_vec);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_redrackham_LSerialPortJNI_native_1setLSerialPortDataListener(JNIEnv *env, jobject thiz,
                                                                      jstring path,
                                                                      jobject listener) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);

    jobject jListener = env->NewGlobalRef(listener);
    mLSerialPortManager->setLSerialPortDataListener(path_str, &jListener);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_redrackham_LSerialPortJNI_native_1closeSerialPort(JNIEnv *env, jobject thiz,
                                                           jstring path) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);
    int result = mLSerialPortManager->removeDevice(path_str);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);
    return result;
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_redrackham_LSerialPortJNI_native_1hasOpen(JNIEnv *env, jobject thiz, jstring path) {
    const char *path_char = env->GetStringUTFChars(path, nullptr);
    auto path_str = std::string(path_char);
    bool result = mLSerialPortManager->hasDevice(path_str);
    //释放资源
    env->ReleaseStringUTFChars(path, path_char);
    return result;
}



extern "C"
JNIEXPORT void JNICALL
Java_com_redrackham_LSerialPortJNI_native_1syncWrite(JNIEnv *env, jobject thiz,
                                                     jlong device_ptr_long,
                                                     jbyteArray data) {
    SyncReadWriteWorker *worker = reinterpret_cast<SyncReadWriteWorker *>(device_ptr_long);
    if (worker != nullptr) {
        std::vector<uint8_t> msg_vec = convertJByteArrayToVectorU8(env, data);
        worker->doWork(msg_vec);
    }
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_redrackham_LSerialPortJNI_native_1syncRead(JNIEnv *env, jobject thiz,
                                                    jlong device_ptr_long) {
    SyncReadWriteWorker *worker = reinterpret_cast<SyncReadWriteWorker *>(device_ptr_long);
    jbyteArray jData;
    if (worker != nullptr) {
        auto msg_vec = worker->read();
        auto size = static_cast<uint32_t>(msg_vec.size());
        if (size > static_cast<uint32_t>(std::numeric_limits<jsize>::max())) {
            LOGE("data size is too big, splitting data into chunks!");
            // 数据过大，需要分段拷贝
            constexpr uint32_t chunkSize = std::numeric_limits<jsize>::max();
            jData = env->NewByteArray(chunkSize);
            uint32_t offset = 0;
            while (offset < size) {
                const uint32_t copySize = std::min(size - offset, chunkSize);
                // 创建临时的 jbyteArray 用于存储当前分段的数据
                jbyteArray tempData = env->NewByteArray(static_cast<jsize>(copySize));
                env->SetByteArrayRegion(tempData, 0, static_cast<jsize>(copySize),
                                        reinterpret_cast<const jbyte *>(msg_vec.data() + offset));
                // 将当前分段的数据拷贝到最终的 jData 中
                env->SetByteArrayRegion(jData, 0, static_cast<jsize>(copySize),
                                        reinterpret_cast<const jbyte *>(msg_vec.data() + offset));
                offset += copySize;
                // 释放临时的 jbyteArray
                env->DeleteLocalRef(tempData);
            }
        } else {
            jData = env->NewByteArray(static_cast<jsize>(size));
            env->SetByteArrayRegion(jData, 0, static_cast<jsize>(size),
                                    reinterpret_cast<const jbyte *>(msg_vec.data()));
        }
    } else {
        jData = env->NewByteArray(0);
    }
    return jData;
}





extern "C"
JNIEXPORT jboolean JNICALL
Java_com_redrackham_LSerialPortJNI_native_1syncDataAvailable(JNIEnv *env, jobject thiz,
                                                             jlong device_ptr_long) {
    SyncReadWriteWorker *worker = reinterpret_cast<SyncReadWriteWorker *>(device_ptr_long);
    if (worker != nullptr) {
        return worker->dataAvailable();
    } else {
        return false;
    }
}




extern "C"
JNIEXPORT jint JNICALL
        Java_com_redrackham_LSerialPortJNI_native_1closeSyncSerialPort(JNIEnv *env, jobject thiz,
jstring path) {

const char *path_char = env->GetStringUTFChars(path, nullptr);
auto path_str = std::string(path_char);
int result = mLSerialPortManager->removeDevice(path_str);
//释放资源
env->ReleaseStringUTFChars(path, path_char);
return result;
}

