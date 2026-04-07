#ifndef DHT11_ESP_NOW_SENDER_H
#define DHT11_ESP_NOW_SENDER_H

#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>

// ==================== 数据结构 ====================
typedef struct {
  float temperature;
  float humidity;
} DHT11_Data;
// ==============================================

class DHT11_ESP_NOW_Sender {
private:
  uint8_t receiverMAC[6];
  DHT dht;
  unsigned long lastSendTime;
  long sendInterval;

  // 发送回调（静态成员用于中断处理）
  static void onDataSent(const uint8_t *mac, esp_now_send_status_t status);

public:
  // 构造函数
  DHT11_ESP_NOW_Sender(uint8_t dhtPin, uint8_t dhtType, long interval = 2000);

  // 初始化函数
  bool begin(uint8_t mac0, uint8_t mac1, uint8_t mac2, uint8_t mac3, uint8_t mac4, uint8_t mac5);

  // 读取并发送传感器数据
  bool sendData();

  // 设置发送间隔（毫秒）
  void setSendInterval(long interval);

  // 检查是否应该发送数据
  bool shouldSend();

  // 手动读取传感器数据（不发送）
  DHT11_Data readSensor();
};

#endif
