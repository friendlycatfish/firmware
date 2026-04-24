#ifndef __WIFI_ATKS_H__
#define __WIFI_ATKS_H__

#include <WiFi.h>
#include <vector>

// --- 1. CẤU TRÚC FRAME NAGAMI ULTIMATE (BẮT BUỘC) ---
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

// --- 2. BIẾN NGOẠI VI (EXTERN) ---
extern wifi_ap_record_t ap_record;
extern const uint8_t _default_target[6];
extern uint8_t deauth_frame[]; 
extern uint8_t targetBssid[6];
extern uint16_t nagami_reasons[]; // Khai báo để dùng chung danh sách mã lỗi

// Mảng mẫu cũ (giữ lại để không lỗi các hàm nguyên bản của Bruce)
const uint8_t deauth_frame_default[] = {0xc0, 0x00, 0x3a, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x02, 0x00};

// --- 3. CÁC HÀM THỰC THI (PROTOTYPES) ---

/**
 * @brief Lõi bắn Deauth Nagami Ultimate
 * da: Destination (Victim/Broadcast), sa: Source (AP), bssid: AP BSSID, reason: Mã lỗi
 */
void nagami_ultimate_fire(uint8_t* da, uint8_t* sa, uint8_t* bssid, uint16_t reason);

// Các hàm gốc và công cụ
void send_raw_frame(const uint8_t *frame_buffer, int size);
void wsl_bypasser_send_raw_frame(const wifi_ap_record_t *ap_record, uint8_t chan, const uint8_t target[6] = _default_target);
void wifi_atk_info(String tssid, String mac, uint8_t channel);
void wifi_atk_menu();
void target_atk_menu(String tssid, String mac, uint8_t channel);

// Chế độ Deauth Single (Đã nâng cấp Nagami)
void target_atk(String tssid, String mac, uint8_t channel);

// Các tính năng khác
void capture_handshake(String tssid, String mac, uint8_t channel);
void beaconAttack();
void deauthFloodAttack();

// Chế độ Multi và Top 5 (Dùng lõi Nagami Ultimate)
void deauthTop5Attack();
void deauthMultiAttack();
void execute_multi_bruce_style(const std::vector<wifi_ap_record_t>& targets);

#endif
