#include <stdio.h>
#include <string.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;
    float operatingHours;
    float totalKWh = 0.0f;
    double totalCost = 0.0;

    printf("=== HE THONG QUAN LY PHONG THONG MINH ===\n\n");

    printf("--- NHAP THONG TIN THIET BI ---\n");
    printf("Nhap Ma thiet bi (ID): ");
    scanf("%d", &device.deviceID);
    getchar();
    printf("Nhap Ten thiet bi: ");
    fgets(device.deviceName, sizeof(device.deviceName), stdin);
    device.deviceName[strcspn(device.deviceName, "\n")] = 0;
    printf("Nhap Trang thai (1 - Bat, 0 - Tat): ");
    scanf("%d", &device.status);
    printf("Nhap Cong suat dinh muc (kW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("\n--- NHAP THONG TIN CAM BIEN ---\n");
    printf("Nhap Dien ap do duoc (V): ");
    scanf("%f", &sensor.voltageVolts);
    printf("Nhap Dong dien do duoc (A): ");
    scanf("%f", &sensor.currentAmperes);
    printf("Nhap Thoi gian vang nguoi (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("\nNhap So gio hoat dong trong thang (gio): ");
    scanf("%f", &operatingHours);

    if (sensor.voltageVolts < 0.0f || sensor.currentAmperes < 0.0f || sensor.unoccupancyMinutes < 0) {
        printf("\n[LOI HE THONG] Phat hien thong so cam bien bat thuong.\n");
        return 1;
    }

    if (operatingHours <= 0.0f || operatingHours > 744.0f) {
        printf("\n[LOI DU LIEU] So gio van hanh khong hop le.\n");
        return 1;
    }

    printf("\n================ BAO CAO HE THONG ================\n");

    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;
        printf("[CANH BAO NGUY HIEM] Dong dien vuot nguong an toan (%.2fA > 30.0A)!\n", sensor.currentAmperes);
        printf("=> KICH HOAT CHEDO NGAT KHAN CAP.\n");
    } else if (device.status == 1 && sensor.unoccupancyMinutes >= 15) {
        device.status = 0;
        printf("[TIET KIEM DIEN] Phong vang nguoi lien tuc %d phut.\n", sensor.unoccupancyMinutes);
        printf("=> TU DONG TAT thiet bi '%s'.\n", device.deviceName);
    } else {
        printf("[TRANG THAI AN TOAN] Khong co vi pham.\n");
    }

    totalKWh = device.ratedPowerKW * operatingHours;
    float remainingKWh = totalKWh;

    if (remainingKWh > 0.0f) {
        float kWhInBac1 = (remainingKWh > 50.0f) ? 50.0f : remainingKWh;
        totalCost += kWhInBac1 * 1806.0;
        remainingKWh -= kWhInBac1;
    }

    if (remainingKWh > 0.0f) {
        float kWhInBac2 = (remainingKWh > 50.0f) ? 50.0f : remainingKWh;
        totalCost += kWhInBac2 * 1866.0;
        remainingKWh -= kWhInBac2;
    }

    if (remainingKWh > 0.0f) {
        float kWhInBac3 = (remainingKWh > 100.0f) ? 100.0f : remainingKWh;
        totalCost += kWhInBac3 * 2167.0;
        remainingKWh -= kWhInBac3;
    }

    if (remainingKWh > 0.0f) {
        totalCost += remainingKWh * 2729.0;
    }

    printf("\n--- THONG TIN HOAT DONG SAN PHAM ---\n");
    printf("Ma thiet bi        : %d\n", device.deviceID);
    printf("Ten thiet bi       : %s\n", device.deviceName);
    printf("Trang thai hien tai: %s\n", device.status ? "DANG BAT" : "DA TAT");
    printf("Dien ap / Dong dien : %.1f V / %.1f A\n", sensor.voltageVolts, sensor.currentAmperes);
    printf("Thoi gian vang nguoi: %d phut\n", sensor.unoccupancyMinutes);

    printf("\n--- BAO CAO TIEN DIEN DU KIEN (EVN) ---\n");
    printf("So gio van hanh    : %.1f gio/thang\n", operatingHours);
    printf("Tong dien nang     : %.2f kWh\n", totalKWh);
    printf("Tong tien dien     : %.0f VNĐ (Chua bao gom VAT)\n", totalCost);
    printf("==================================================\n");

    return 0;
}