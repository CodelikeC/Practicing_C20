# **🔥 CONCEPTS – KIẾM PHÁP ĐẠI THỪA CỦA TEMPLATE 🔥**  
💥 **Concepts giúp kiểm soát template ngay từ biên dịch, không còn lỗi dài ngoằng vô nghĩa!**  
💥 **Tối ưu hóa generic programming, đảm bảo code mạnh mẽ và dễ đọc!**  

---

## **🥷 I. CONCEPTS CƠ BẢN – "BƯỚC VÀO CỬA PHẬT"**  
🔥 **Concepts giúp template chỉ nhận kiểu dữ liệu phù hợp. Không còn `enable_if` rối rắm!**  
🔥 **Thay thế `typename` hoặc `class` trong template để có ràng buộc rõ ràng!**  

💡 **Ví dụ: Ràng buộc kiểu số (`Integral`)**
```cpp
#include <iostream>
#include <concepts>

// ✅ Chỉ chấp nhận kiểu số nguyên (int, long, short,...)
template <std::integral T>
T square(T x) {
    return x * x;
}

int main() {
    std::cout << square(5) << '\n';  // ✅ Hợp lệ
    // std::cout << square(5.5) << '\n';  // ❌ Lỗi: 5.5 không phải số nguyên!
}
```
💥 **Nếu truyền `double`, trình biên dịch báo lỗi ngay lập tức!**  
💥 **Không cần `static_assert`, không cần `enable_if`, code vẫn sạch và chặt chẽ!**  

---

## **🥷 II. CONCEPTS TÙY CHỈNH – "CHÂN TRUYỀN CỦA MÔN PHÁI"**  
🔥 **Tạo concept riêng, đặt quy tắc cho kiểu dữ liệu của riêng mình!**  
🔥 **Concept có thể kiểm tra nhiều điều kiện một lúc!**  

💡 **Ví dụ: Chỉ chấp nhận kiểu có `size()`**
```cpp
#include <iostream>
#include <concepts>
#include <vector>
#include <list>

// ✅ Concept yêu cầu kiểu dữ liệu có phương thức size()
template <typename T>
concept HasSize = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};

// ✅ Hàm chỉ nhận kiểu có size()
template <HasSize T>
void printSize(const T& container) {
    std::cout << "Size: " << container.size() << '\n';
}

int main() {
    std::vector<int> v{1, 2, 3};
    std::list<int> l{1, 2, 3, 4};

    printSize(v);  // ✅ Được vì vector có size()
    printSize(l);  // ✅ Được vì list có size()
    // printSize(42);  // ❌ Lỗi: int không có size()
}
```
💥 **Concept `HasSize` giúp giới hạn template chỉ nhận kiểu có `size()`!**  
💥 **Code rõ ràng hơn, không cần overload nhiều hàm kiểm tra kiểu!**  

---

## **🥷 III. COMBINE CONCEPTS – "HỢP BÍ KÍP, TẠO TỨC HỢP NHẤT KIẾM"**  
🔥 **Concepts có thể kết hợp với nhau bằng `&&`, `||` để tạo điều kiện phức tạp!**  
🔥 **Dễ đọc hơn nhiều so với `std::enable_if`!**  

💡 **Ví dụ: Chỉ chấp nhận kiểu số nguyên hoặc có `size()`**
```cpp
#include <iostream>
#include <concepts>
#include <vector>

// ✅ Concept yêu cầu kiểu là số nguyên hoặc có size()
template <typename T>
concept ValidType = std::integral<T> || requires(T t) { { t.size() } -> std::convertible_to<std::size_t>; };

// ✅ Chỉ nhận kiểu hợp lệ
template <ValidType T>
void process(const T& value) {
    std::cout << "Processing...\n";
}

int main() {
    process(42);         // ✅ Hợp lệ (số nguyên)
    process(std::vector<int>{1, 2, 3});  // ✅ Hợp lệ (vector có size())
    // process(3.14);    // ❌ Lỗi: double không hợp lệ!
}
```
💥 **Kết hợp nhiều concept trong một câu lệnh, kiểm tra linh hoạt hơn!**  
💥 **Không còn phải viết nhiều `if constexpr`, code ngắn gọn mà vẫn mạnh mẽ!**  

---

## **🥷 IV. CONCEPTS + AUTO – "NHẸ NHƯ GIÓ, LINH HOẠT VÔ BIÊN"**  
🔥 **Concepts có thể dùng với `auto`, giúp code vừa linh hoạt vừa có kiểm soát!**  
🔥 **Tạo kiểu dữ liệu "tự động nhưng có kỷ luật"!**  

💡 **Ví dụ: `auto` với concept**
```cpp
#include <iostream>
#include <concepts>

// ✅ Concept yêu cầu kiểu số nguyên
template <std::integral T>
auto half(T x) {
    return x / 2;
}

int main() {
    std::cout << half(10) << '\n';  // ✅ Được (int hợp lệ)
    // std::cout << half(3.14) << '\n';  // ❌ Lỗi: double không hợp lệ!
}
```
💥 **Kết hợp `auto` với `concepts`, code vừa tự động vừa chặt chẽ!**  

---

# **🔥 Lời kết – Concepts: Thượng thừa kiếm pháp template! 🔥**  
✅ **Không còn lỗi template dài ngoằng khó hiểu!**  
✅ **Không cần `std::enable_if`, code ngắn hơn, dễ đọc hơn!**  
✅ **Giới hạn kiểu dữ liệu ngay từ đầu, tối ưu hóa compile-time!**  

💥 **Đạo hữu đã lĩnh hội pháp môn Concepts, tiếp theo muốn thám hiểm vùng đất nào?**  
⚔ **`std::format` – Kiếm pháp định dạng chuỗi như nghệ thuật?**  
⚔ **`constexpr` nâng cao – "Đệ nhất tông sư tính toán compile-time"?**  
⚔ **Hay tiến sâu vào `lock-free`, memory order, tranh bá thiên hạ?**