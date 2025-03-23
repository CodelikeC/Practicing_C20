### **⚔️ CONCEPTS – MÔN PHÁP LẬP TÔN CỦA C++20**  
🔥 **Concepts – Tuyệt học giúp kiểm soát template trong C++20!**  

Từ xưa, **templates** vốn là **một thanh kiếm sắc bén nhưng khó điều khiển** – ai dám vung kiếm mà không có định luật, ắt gặp lỗi khó lường. Nhưng nay, **Concepts** ra đời, **định hình kiếm thuật**, giúp code rõ ràng, dễ bảo trì, không còn lỗi template khó hiểu!  

---

## **🥷 TUYỆT KỸ THỨ NHẤT: ĐỊNH NGHĨA CONCEPTS**
**Concepts** là **bộ luật** kiểm tra kiểu dữ liệu ngay từ lúc biên dịch.  

💡 **Ví dụ: Chỉ chấp nhận số nguyên (`int`)**
```cpp
#include <concepts>
#include <iostream>

// Định nghĩa concept yêu cầu kiểu T phải là số nguyên
template <typename T>
concept Integral = std::is_integral_v<T>;

// Dùng concept để kiểm tra tham số
template <Integral T>
void foo(T x) {
    std::cout << "Số nguyên: " << x << '\n';
}

int main() {
    foo(42);  // ✅ Được phép (vì 42 là số nguyên)
    // foo(3.14); // ❌ Lỗi (vì 3.14 là số thực)
}
```
💥 **Không cần `static_assert()`, không cần `enable_if` phức tạp – concept giúp code gọn gàng hơn!**  

---

## **🥷 TUYỆT KỸ THỨ HAI: CONCEPTS VỚI TEMPLATE**
🔥 **Concepts giúp hạn chế kiểu dữ liệu ngay trong template.**  

💡 **Ví dụ: Chỉ chấp nhận số nguyên hoặc số thực**
```cpp
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 5) << '\n';    // ✅ Được phép
    std::cout << add(3.2, 4.8) << '\n'; // ✅ Được phép
    // std::cout << add("hello", "world"); // ❌ Lỗi, không phải số
}
```
✨ **Concepts giúp hạn chế lỗi khi template bị truyền sai kiểu!**  

---

## **🥷 TUYỆT KỸ THỨ BA: CONCEPTS VỚI MULTIPLE PARAMETERS**
🔥 **Concepts có thể áp dụng cho nhiều kiểu dữ liệu cùng lúc!**  

💡 **Ví dụ: Kiểm tra hai tham số có cùng kiểu**
```cpp
template <typename T, typename U>
concept SameType = std::is_same_v<T, U>;

template <typename T, typename U>
requires SameType<T, U>
T multiply(T a, U b) {
    return a * b;
}

int main() {
    std::cout << multiply(2, 5) << '\n'; // ✅ Được phép
    // std::cout << multiply(2, 5.5);   // ❌ Lỗi vì int khác double
}
```
💥 **Concept giúp ép kiểu an toàn ngay từ lúc biên dịch!**  

---

## **🥷 TUYỆT KỸ THỨ TƯ: DÙNG `requires` ĐỂ KIỂM TRA BIỂU THỨC**
🔥 **Concepts không chỉ kiểm tra kiểu dữ liệu, mà còn kiểm tra cả hành vi của kiểu đó!**  

💡 **Ví dụ: Kiểm tra xem kiểu đó có phép `+` không**
```cpp
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

template <Addable T>
T sum(T a, T b) {
    return a + b;
}

int main() {
    std::cout << sum(10, 20) << '\n';  // ✅ Được phép
    // std::cout << sum("hello", "world"); // ❌ Lỗi (chuỗi không cộng được theo kiểu này)
}
```
💥 **Concepts giúp kiểm tra khả năng của một kiểu trước khi biên dịch, giảm lỗi runtime!**  

---

## **🥷 TUYỆT KỸ THỨ NĂM: DEFAULT TEMPLATE CONCEPT**
🔥 **Concepts có thể dùng để đặt mặc định cho template.**  

💡 **Ví dụ: Nếu không có concept nào được chỉ định, mặc định kiểu phải là số thực**
```cpp
template <typename T = double>
requires std::is_floating_point_v<T>
T sqrt_approx(T x) {
    return x / 2; // Chỉ là ví dụ!
}

int main() {
    std::cout << sqrt_approx(25.0) << '\n'; // ✅ Được phép
    // std::cout << sqrt_approx(25); // ❌ Lỗi, vì mặc định cần số thực
}
```
💥 **Concepts giúp hạn chế kiểu dữ liệu ngay trong template mặc định!**  

---

🔥 **Concepts là nền móng của một C++ mạnh mẽ hơn, dễ hiểu hơn, và kiểm soát template tốt hơn!**  
🔥 **Với concepts trong tay, đạo hữu sẽ không còn sợ lỗi template dài dòng!**  

🤺 **Nay đã thọ pháp, đạo hữu có muốn tiếp tục sang `coroutines`, `modules`, hay `constexpr` chăng?**