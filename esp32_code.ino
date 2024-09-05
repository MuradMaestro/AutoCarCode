#include "esp_camera.h"
#include <WiFi.h>
#include <HardwareSerial.h>

// UART interfeysi üçün Serial1
HardwareSerial mySerial(1);

void setup() {
  Serial.begin(115200);
  
  // UART interfeysi üçün pinləri təyin edin
  mySerial.begin(115200, SERIAL_8N1, 16, 17); // GPIO16 (RX), GPIO17 (TX)
  
  // ESP32-CAM qurulması (kamera parametrlərini daxil edin)
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // Kamera başlatması
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Kamera başlatıla bilmədi, xəta: 0x%x", err);
    return;
  }

  // WiFi qurulması (əgər lazımdırsa)
}

void loop() {
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  
  if (!fb) {
    Serial.println("Kamera görüntüsü alınmadı");
    return;
  }

  // Burada obyekt tanıma alqoritmini yerləşdirin
  // Məsələn, yol və ya obyekt tanıyarkən aşağıdakı komandalardan birini göndərin

  bool objectDetected = false; // Burada obyekt tanıma şərtini yazın

  if (objectDetected) {
    mySerial.println("LEFT"); // Sol dön
  } else {
    mySerial.println("FORWARD"); // Düz hərəkət et
  }

  esp_camera_fb_return(fb);
  delay(100);
}
