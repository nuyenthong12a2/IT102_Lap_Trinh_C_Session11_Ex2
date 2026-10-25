#include <stdio.h>
#define MAX_SHELF_WEIGHT 500.0

// C?u trúc bi?u di?n thông tin ki?n hàng Pallet
typedef struct {
    int pallet_id;
    float weight_kg;
    float temp_celsius;
} PalletItem;


typedef struct {
    int shelf_id;
    int is_cold_storage;
    float current_weight_kg;
} WarehouseShelf;


int kiem_tra_an_toan_nhap_kho(WarehouseShelf shelf, PalletItem item) {
    
    if (shelf.is_cold_storage == 1) {
        
        if (item.temp_celsius < -18.0 || item.temp_celsius > 5.0) {
            printf("[L?I KHO L?NH] Nhi?t ð? b?o qu?n %.1f°C không ð?t chu?n (-18°C ð?n 5°C)!\n", item.temp_celsius);
            return 0;
        }
    }

    // 2. Ki?m tra gi?i h?n t?i tr?ng t?i ða c?a ô k? sau khi x?p thêm ki?n hàng m?i
    float tong_tai_trong = shelf.current_weight_kg + item.weight_kg;
    if (tong_tai_trong > MAX_SHELF_WEIGHT) {
        printf("[L?I QUÁ T?I] T?ng t?i tr?ng d? ki?n %.1f kg (Hi?n t?i: %.1f kg + M?i: %.1f kg) vý?t gi?i h?n t?i ða %.1f kg!\n", 
               tong_tai_trong, shelf.current_weight_kg, item.weight_kg, MAX_SHELF_WEIGHT);
        return 0;
    }

    return 1;
}

int main() {
    // Kh?i t?o ô k? 101 ðang lýu tr? 400.0 kg hàng trong phân khu kho l?nh
    WarehouseShelf ke_lanh_101 = {101, 1, 400.0};

    // Ki?n hàng pallet m?i: N?ng 150.0 kg, Nhi?t ð? b?o qu?n 12.0°C
    PalletItem pallet_moi = {5001, 150.0, 12.0};

    printf("=== H? TH?NG GIÁM SÁT AN TOÀN NH?P KHO LOGISTICS ===\n");
    printf("Thông tin k? 101 : T?i tr?ng hi?n t?i = %.1f kg | Lo?i kho = %s\n", 
           ke_lanh_101.current_weight_kg, 
           ke_lanh_101.is_cold_storage ? "Kho L?nh" : "Kho Thý?ng");
    printf("Ki?n hàng nh?p   : M? = %d | N?ng = %.1f kg | Nhi?t ð? = %.1f°C\n",
           pallet_moi.pallet_id, pallet_moi.weight_kg, pallet_moi.temp_celsius);
    printf("----------------------------------------------------\n");

    int ket_qua = kiem_tra_an_toan_nhap_kho(ke_lanh_101, pallet_moi);

    if (ket_qua == 1) {
        printf("=> K?T QU?: [DUY?T] Ð? ði?u ki?n nh?p kho!\n");
    } else {
        printf("=> K?T QU?: [T? CH?I] Vi ph?m quy ð?nh an toàn lýu kho!\n");
    }

    return 0;
}
