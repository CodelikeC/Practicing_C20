**🔥 BỘ BA TUYỆT KỸ C++20 – LẬP TRÌNH NHƯ KIẾM KHÁCH, THIÊN HẠ BẤT BẠI! 🔥**  

🌀 **1. COROUTINES – TUYỆT CHIÊU NÉ TRÁNH BLOCKING, ĐỆ NHẤT PHÁP ASYNC**  
🌀 **2. MODULES – HÓA GIẢI INCLUDE, ĐƯỜNG KIẾM CẮT BIÊN DỊCH NHƯ GIÓ**  
🔥 **3. THREE-WAY COMPARISON (`<=>`) – TUYỆT CHIÊU "SO SÁNH THIÊN HẠ"**  

Đạo hữu hãy nhập môn từng tuyệt học!  

---

## **🥷 COROUTINES – VÔ ẢNH BỘ PHÁP CỦA ASYNC**  
🔥 **Coroutines (hàm đồng bộ hóa) giúp chương trình không bị blocking**  
🔥 **Không còn chờ đợi vô nghĩa, không cần thread thừa thãi!**  

💡 **Ví dụ: `co_await` – Kích hoạt coroutine**
```cpp
#include <iostream>
#include <coroutine>
#include <chrono>
#include <thread>

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

Task delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    co_return;
}

Task asyncTask() {
    std::cout << "Bắt đầu...\n";
    co_await delay(2000);
    std::cout << "Xong!\n";
}

int main() {
    asyncTask();  // ✅ Không blocking main thread
    std::cout << "Chương trình không bị chặn!\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
```
💥 **Với `co_await`, chương trình có thể tiếp tục chạy mà không chặn main thread!**  
💥 **Không cần mutex, không cần thread phức tạp, vẫn có async dễ dàng!**  

---

## **🥷 MODULES – HÓA GIẢI "INCLUDE HELL"**  
🔥 **Modules giúp biên dịch nhanh hơn, code sạch hơn, không còn cần `#include` rườm rà!**  
🔥 **Giảm `#pragma once`, giảm lỗi `#define`, giải phóng compile time!**  

💡 **Ví dụ: Tạo module**
```cpp
// math.ixx (Interface Module File)
export module math;

export int add(int a, int b) {
    return a + b;
}
```

💡 **Dùng module trong main**
```cpp
import math;
#include <iostream>

int main() {
    std::cout << add(5, 3) << '\n';  // ✅ Không cần `#include`!
}
```
💥 **Không còn `#include`, không còn lỗi `#define` chồng chéo!**  
💥 **Compile nhanh hơn, không cần precompiled headers!**  

---

## **🥷 THREE-WAY COMPARISON (`<=>`) – "SO SÁNH THIÊN HẠ"**  
🔥 **Chỉ cần một phép toán `<=>`, thay thế toàn bộ `==`, `<`, `>`, `<=`, `>=`, `!=`**  
🔥 **Tự động suy luận kết quả, tối ưu hơn cho các cấu trúc dữ liệu phức tạp!**  

💡 **Ví dụ: So sánh hai số**
```cpp
#include <iostream>
#include <compare>

int main() {
    std::cout << (10 <=> 20 < 0) << '\n'; // ✅ -1 (10 nhỏ hơn 20)
    std::cout << (10 <=> 10 == 0) << '\n'; // ✅ 1 (10 bằng 10)
    std::cout << (20 <=> 10 > 0) << '\n'; // ✅ 1 (20 lớn hơn 10)
}
```

💡 **Ví dụ: Dùng `<=>` trong `struct`**
```cpp
#include <iostream>
#include <compare>

struct Warrior {
    int power;
    auto operator<=>(const Warrior&) const = default; // ✅ Tự động so sánh
};

int main() {
    Warrior w1{100}, w2{200};
    std::cout << (w1 < w2) << '\n';  // ✅ Đúng (100 < 200)
}
```
💥 **Không cần viết từng phép so sánh `==`, `<`, `>` riêng lẻ nữa!**  
💥 **Dễ bảo trì hơn, code ngắn gọn hơn, và tối ưu hơn!**  

---

**🔥 Đạo hữu đã lĩnh hội ba môn tuyệt kỹ C++20. Giờ đây, đạo hữu muốn bước tiếp trên con đường nào?**  
💥 **Chinh phục `constexpr`, tiến vào `std::format`, hay tiếp tục với `concepts` nâng cao?**