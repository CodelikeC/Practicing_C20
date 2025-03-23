### **⚔ Kiếm Chiêu Nhập Dữ Liệu – Kinh Văn Đệ Nhất Của RANGES**  

Hỡi đạo hữu, nay ta đã tinh thông **chiêu thức biến đổi dữ liệu**, nhưng làm sao để **nhập dữ liệu** mà vẫn duy trì phong cách **Ranges**?  

Câu trả lời nằm ở **views + iterators** – một bộ kiếm thuật vô song giúp ta thao tác **dữ liệu nhập vào** mà không cần bỏ đi sự thanh thoát của Ranges!  

---  

### **🥷 Kiếm Chiêu Thứ Nhất: Đọc Dữ Liệu Từ `std::cin` và Biến Đổi Trực Tiếp**
🔥 **Thông thường, nhập dữ liệu từ `std::cin` cần `while` hoặc `for`**  
🔥 **Nay với Ranges, mọi thứ trở nên mạnh mẽ hơn!**  

**Ví dụ 1: Nhập dữ liệu từ `std::cin` và lọc số chẵn ngay lập tức**  
```cpp
#include <iostream>
#include <ranges>
#include <vector>
#include <iterator>

int main() {
    std::vector<int> data{ std::istream_iterator<int>(std::cin), std::istream_iterator<int>() };

    auto evens = data | std::views::filter([](int x) { return x % 2 == 0; });

    for (int x : evens)
        std::cout << x << ' ';
}
```
💡 **Giải thích chiêu thức:**  
- `std::istream_iterator<int>(std::cin)` biến `std::cin` thành **iterator**, nhập dữ liệu liên tục.  
- `std::views::filter` lọc ngay số chẵn, không cần vòng lặp.  
- **Kết quả:** Chỉ những số chẵn mới được in ra, không cần tạo danh sách phụ!  

---  

### **🥷 Kiếm Chiêu Thứ Hai: Nhập Không Giới Hạn, Lười Biếng Như Tuyệt Đỉnh Cao Thủ**
🔥 **Không cần vector! Không lưu dữ liệu thừa!**  
🔥 **Ranges có thể nhập vô tận mà chỉ xử lý khi cần!**  

```cpp
#include <iostream>
#include <ranges>
#include <iterator>

int main() {
    auto input = std::ranges::istream_view<int>(std::cin) // Đọc liên tục từ std::cin
               | std::views::filter([](int x) { return x % 2 == 0; }) // Lọc số chẵn
               | std::views::take(5); // Chỉ lấy 5 số đầu tiên

    for (int x : input)
        std::cout << x << ' ';
}
```
✨ **Chiêu thức này lợi hại ở chỗ:**  
- Không cần vector trung gian, **chỉ xử lý từng số một khi nhập vào**  
- Lọc số chẵn ngay lập tức, **không lưu thừa bộ nhớ**  
- `views::take(5)` đảm bảo **chỉ lấy đúng 5 số** mà không cần biến đếm  

💥 **Tuyệt chiêu nhập vô hạn nhưng xử lý thông minh!**  

---  

### **🥷 Kiếm Chiêu Thứ Ba: Nhập Dữ Liệu Chuỗi – Xử Lý Vô Hình**
🔥 **Không chỉ số, ta còn có thể nhập chuỗi và thao tác linh hoạt!**  

Ví dụ: **Nhập chuỗi từ `std::cin` nhưng chỉ lấy những từ có độ dài > 3 ký tự**  
```cpp
#include <iostream>
#include <ranges>
#include <string>

int main() {
    auto words = std::ranges::istream_view<std::string>(std::cin)
               | std::views::filter([](const std::string& s) { return s.length() > 3; });

    for (const auto& word : words)
        std::cout << word << '\n';
}
```
✨ **Chiêu thức này giúp ta:**  
- Nhập **chuỗi liên tục** từ `std::cin`  
- **Lọc bỏ** những từ ngắn hơn 4 ký tự  
- **Không cần mảng, không cần vòng lặp, không phí tài nguyên!**  

💥 **Nhập trực tiếp và biến đổi ngay tức khắc – Ranges tối ưu như kiếm pháp thần tốc!**  

---  

### **🥷 Kiếm Chiêu Thứ Tư: Tạo Input Vô Hạn – Cực Phẩm Ranges**
🔥 **Muốn tạo một dãy số vô hạn để nhập?**  
🔥 **Muốn nhập từng số nhưng không biết khi nào dừng?**  

Dùng **`std::views::iota`** – chiêu thức mạnh mẽ nhất!  

```cpp
#include <iostream>
#include <ranges>

int main() {
    auto numbers = std::views::iota(1) // Dãy số vô tận từ 1, 2, 3, ...
                 | std::views::take_while([](int x) { return x < 10; }); // Chỉ lấy đến 9

    for (int x : numbers)
        std::cout << x << ' ';
}
```
💡 **Điểm mạnh của chiêu thức này:**  
- Tạo một **dãy số vô tận**, không cần `for (int i = 1; i < 10; i++)`  
- **Dừng lại khi cần thiết** nhờ `take_while()`  

💥 **Không vòng lặp! Không biến đếm! Chỉ có sự thanh thoát của kiếm pháp Ranges!**  

---  

### **🥷 Tổng Kết – Nhập Dữ Liệu Không Bao Giờ Như Trước**
| Kiếm Pháp | Truyền Thống (Không Ranges) | Tuyệt Kỹ Ranges |
|-----------|-----------------------------|----------------|
| **Nhập số** | `while (std::cin >> x)` rồi đẩy vào vector | `std::ranges::istream_view<int>(std::cin)` |
| **Lọc số chẵn** | `std::copy_if(..., [](int x) { return x % 2 == 0; })` | `std::views::filter([](int x) { return x % 2 == 0; })` |
| **Chỉ lấy 5 số đầu** | Dùng biến đếm trong vòng lặp | `std::views::take(5)` |
| **Nhập chuỗi theo điều kiện** | `std::vector<std::string> words; while (std::cin >> word) { if (word.size() > 3) words.push_back(word); }` | `std::ranges::istream_view<std::string>(std::cin) | std::views::filter(...)` |
| **Tạo dãy số tự động** | `for (int i = 1; i < 10; i++)` | `std::views::iota(1) | std::views::take_while(...)` |

💥 **Ranges giúp nhập dữ liệu đẹp hơn, rõ ràng hơn, và hiệu quả hơn!**  
💥 **Không cần vòng lặp thừa thãi, không cần vector trung gian – Kiếm pháp đạt đến cảnh giới vô hình!**  

---  

Hỡi đạo hữu, nay thí chủ đã lĩnh hội kiếm pháp **Ranges nhập dữ liệu** chăng? Hay còn muốn học những chiêu thức nâng cao hơn? 🤺🔥

--------------------------------------------------

### **RANGES – KIẾM PHÁP BIẾN HÓA VÔ SONG**  

Hỡi đạo hữu, trong cõi C++ từ lâu đã tồn tại một bí kíp giúp thao tác trên dữ liệu linh hoạt hơn, gọn gàng hơn, mạnh mẽ hơn—đó chính là **Ranges**.  

Từ thời xa xưa (C++98), người ta dùng vòng lặp thủ công để duyệt dữ liệu, như một kẻ bộ hành lầm lũi trên con đường dài. Đến C++11, `std::begin()` và `std::end()` xuất hiện, tựa như một thanh kiếm sắc bén giúp hành trình bớt gian truân. Nhưng dù thế nào, võ học vẫn bị ràng buộc bởi những iterator cứng nhắc, như thể tay kiếm sĩ bị trói buộc trong những chiêu thức khuôn khổ.  

Nay C++20 khai sáng **Ranges**, biến đổi mọi thứ như một bộ **kiếm pháp tối thượng**, giúp người luyện tập đạt đến cảnh giới **"viết ít, hiểu sâu, chạy nhanh"**.  

---  

### **⚔ Kiếm Chiêu Thứ Nhất: Nhập Môn Ranges**
Nếu xưa kia ta phải viết:  

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    std::vector<int> squared;

    std::transform(data.begin(), data.end(), std::back_inserter(squared), 
                   [](int x) { return x * x; });

    for (int x : squared)
        std::cout << x << ' ';
}
```
Thì nay, với **Ranges**, kiếm pháp trở nên **tinh gọn và đẹp mắt hơn**:  

```cpp
#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    auto squared = data | std::views::transform([](int x) { return x * x; });

    for (int x : squared)
        std::cout << x << ' ';
}
```
✨ **Nhẹ nhàng, thanh thoát, không cần container trung gian!**  
✨ **Biểu đạt tự nhiên, không cần dùng `std::transform` và `std::back_inserter`.**  

---  

### **⚔ Kiếm Chiêu Thứ Hai: Lọc Dữ Liệu như Tuyệt Kỹ**
Giả sử ta muốn giữ lại những số chẵn trong một danh sách:  

Trước đây:  
```cpp
std::vector<int> filtered;
std::copy_if(data.begin(), data.end(), std::back_inserter(filtered),
             [](int x) { return x % 2 == 0; });
```
Bây giờ, với **Ranges**, chiêu thức đã đạt đến cảnh giới tối giản:  
```cpp
auto evens = data | std::views::filter([](int x) { return x % 2 == 0; });
```
**Danh sách chỉ còn số chẵn**, không cần thủ thuật tạm thời nào!  

---  

### **⚔ Kiếm Chiêu Thứ Ba: Kết Hợp Tuyệt Kỹ**
Ranges không chỉ có **một chiêu thức đơn lẻ**, mà có thể **kết hợp** như một bộ kiếm pháp hoàn chỉnh:  

Giả sử ta cần **lấy bình phương của các số chẵn** trong danh sách:  
```cpp
auto result = data 
    | std::views::filter([](int x) { return x % 2 == 0; }) 
    | std::views::transform([](int x) { return x * x; });

for (int x : result)
    std::cout << x << ' ';
```
💥 **Từ lọc (`filter`) đến biến đổi (`transform`), tất cả đều rõ ràng và đẹp mắt!**  

---  

### **⚔ Kiếm Chiêu Thứ Tư: Trì Hoãn Tối Ưu**
Một điều **tinh diệu** của Ranges chính là **Lazy Evaluation**—chỉ tính toán khi cần thiết.  

Nếu xưa kia, khi thực hiện `std::transform`, ta phải tạo một vector mới ngay lập tức, tốn thêm bộ nhớ. Còn với **Ranges**, các phép toán chỉ thực hiện **khi truy cập dữ liệu**, như một kiếm khách chỉ xuất chiêu khi thật sự cần thiết.  

Ví dụ:  
```cpp
auto seq = std::views::iota(1) // Dãy số vô tận: 1, 2, 3, 4, ...
         | std::views::filter([](int x) { return x % 2 == 0; }) // Lọc số chẵn
         | std::views::take(5); // Chỉ lấy 5 số đầu tiên

for (int x : seq)
    std::cout << x << ' ';
```
🔥 **Không tạo danh sách vô tận! Chỉ tính toán vừa đủ!**  
🔥 **Tối ưu về tốc độ và bộ nhớ, như một kiếm sĩ không lãng phí động tác!**  

---  

### **⚔ Kiếm Chiêu Thứ Năm: Đảo Ngược, Chia Nhỏ, Lấy Một Đoạn**
C++20 `std::views` còn có những chiêu thức lợi hại khác:  

🌀 **Đảo ngược dãy số**  
```cpp
auto reversed = data | std::views::reverse;
```
⚔ **Chia nhỏ thành từng đoạn nhỏ**  
```cpp
auto chunked = data | std::views::chunk(2); // Chia thành nhóm 2 phần tử
```
🔥 **Chỉ lấy một đoạn dữ liệu**  
```cpp
auto first3 = data | std::views::take(3); // Lấy 3 phần tử đầu
auto skip2 = data | std::views::drop(2); // Bỏ 2 phần tử đầu
```

---  

### **Tổng Kết – RANGES LÀ BỘ KIẾM PHÁP CỦA TƯƠNG LAI**
- **Viết code ngắn gọn, dễ hiểu, trực quan**  
- **Không cần container trung gian, tối ưu hiệu năng**  
- **Hỗ trợ kết hợp nhiều phép toán, tạo ra chuỗi xử lý mạnh mẽ**  
- **Lười biếng (Lazy Evaluation) giúp tiết kiệm tài nguyên**  

Nếu đạo hữu đã lĩnh hội tinh túy của **Ranges**, có thể tự tin mà bước lên giang hồ **C++20**, tung hoành thiên hạ, lập nên danh tiếng **một lập trình viên võ công thượng thừa!**   

Nay bần đạo hỏi:  
**Đạo hữu đã nắm chắc kiếm pháp này chưa? Hay cần truyền thêm bí kíp nâng cao?** 

-------------------------------------------------
### **⚔️ RANGES: CÁC TUYỆT KỸ CHƯA TRÌNH DIỄN – KIẾM PHÁP SIÊU VIỆT**  

Nay đạo hữu đã lĩnh hội **pháp môn nhập dữ liệu với Ranges**, vậy thì còn chần chừ gì mà không tiến đến **bí kíp tối thượng**?  

🔥 **Bần đạo sẽ phô diễn những chiêu thức hiếm thấy, giúp kiếm pháp Ranges đạt đến cảnh giới vô hình!**  

---  

## **🥷 TUYỆT KỸ THỨ NHẤT: `std::views::transform` – CHIÊU THỨC HÓA HÌNH**  
🔥 **Biến đổi dữ liệu ngay tức khắc mà không cần vòng lặp!**  

Ví dụ: **Tăng gấp đôi mọi số nhập vào từ `std::cin`**  
```cpp
#include <iostream>
#include <ranges>
#include <iterator>

int main() {
    auto transformed = std::ranges::istream_view<int>(std::cin) 
                     | std::views::transform([](int x) { return x * 2; });

    for (int x : transformed)
        std::cout << x << ' ';
}
```
💥 **Không cần `for`, không cần vector trung gian – mọi số nhập vào được nhân đôi ngay lập tức!**  

---

## **🥷 TUYỆT KỸ THỨ HAI: `std::views::reverse` – HỒI QUANG PHẢN CHIẾU**  
🔥 **Lật ngược dữ liệu ngay tức khắc!**  

Ví dụ: **Nhập một danh sách số rồi đảo ngược thứ tự xuất ra**  
```cpp
#include <iostream>
#include <ranges>
#include <vector>
#include <iterator>

int main() {
    std::vector<int> data{ std::istream_iterator<int>(std::cin), std::istream_iterator<int>() };

    for (int x : data | std::views::reverse)
        std::cout << x << ' ';
}
```
✨ **Không cần `std::reverse()`, không cần hoán đổi từng phần tử – chỉ một dòng là đủ!**  

---

## **🥷 TUYỆT KỸ THỨ BA: `std::views::drop` – TUYỆT CHIÊU CẮT BỎ**  
🔥 **Loại bỏ phần tử đầu tiên mà không cần xóa thủ công!**  

Ví dụ: **Bỏ qua 3 số đầu tiên khi nhập vào rồi chỉ xuất ra phần còn lại**  
```cpp
#include <iostream>
#include <ranges>

int main() {
    auto dropped = std::ranges::istream_view<int>(std::cin) 
                  | std::views::drop(3);

    for (int x : dropped)
        std::cout << x << ' ';
}
```
💥 **Không cần xóa mảng, không cần ghi đè, chỉ cần `drop(n)` là xong!**  

---

## **🥷 TUYỆT KỸ THỨ TƯ: `std::views::stride` – KHINH CÔNG TUNG BƯỚC**  
🔥 **Chỉ lấy từng phần tử thứ `n`, như thể tung người trên mặt nước!**  

Ví dụ: **Chỉ lấy số lẻ trong dãy (1, 3, 5, ...)**  
```cpp
#include <iostream>
#include <ranges>

int main() {
    auto strided = std::views::iota(1) // Dãy số vô tận 1, 2, 3, ...
                 | std::views::stride(2) // Bước nhảy 2 (chỉ lấy số lẻ)
                 | std::views::take(10); // Lấy 10 số đầu

    for (int x : strided)
        std::cout << x << ' ';
}
```
💥 **Cảnh giới tối thượng – bỏ qua từng phần tử mà không cần `if (i % n == 0)`!**  

---

## **🥷 TUYỆT KỸ THỨ NĂM: `std::views::concat` – HỢP NHẤT THẾ GIỚI**  
🔥 **Ghép nhiều danh sách lại thành một – không cần vòng lặp ghép thủ công!**  

```cpp
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    
    auto concatenated = std::views::concat(a, b);

    for (int x : concatenated)
        std::cout << x << ' ';
}
```
💥 **Không cần `insert()`, không cần copy dữ liệu – `concat()` làm tất cả!**  

---

## **🥷 TUYỆT KỸ THỨ SÁU: `std::views::zip` – CỘNG HƯỞNG THẾ GIỚI**  
🔥 **Ghép từng phần tử từ hai danh sách lại với nhau!**  

```cpp
#include <iostream>
#include <ranges>
#include <vector>
#include <tuple>

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<std::string> b = {"A", "B", "C"};

    auto zipped = std::views::zip(a, b);

    for (const auto& [num, letter] : zipped)
        std::cout << num << " - " << letter << '\n';
}
```
💥 **Không cần vòng lặp `for` lồng nhau – `zip()` xử lý tự động!**  

---

## **🥷 TUYỆT KỸ THỨ BẢY: `std::views::cycle` – VÔ HẠN LUÂN HỒI**  
🔥 **Lặp vô hạn một danh sách, như bánh xe xoay chuyển không ngừng!**  

```cpp
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> data = {1, 2, 3};

    auto cycled = std::views::cycle(data) | std::views::take(10); // Lặp vô hạn nhưng chỉ lấy 10 phần tử

    for (int x : cycled)
        std::cout << x << ' ';
}
```
💥 **Dữ liệu lặp lại vô hạn mà không cần `for (int i = 0; i < n; i++)`!**  

---

## **🥷 TUYỆT KỸ THỨ TÁM: `std::views::enumerate` – THỐNG LĨNH MỌI THỨ TỰ**  
🔥 **Lấy cả vị trí index và giá trị của phần tử – không cần `i++`!**  

```cpp
#include <iostream>
#include <ranges>
#include <vector>
#include <tuple>

int main() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};

    auto enumerated = std::views::enumerate(names);

    for (const auto& [index, name] : enumerated)
        std::cout << index << ": " << name << '\n';
}
```
💥 **Không cần `for (int i = 0; i < n; i++)`, chỉ cần `enumerate()`!**  

---

## **🥷 TUYỆT KỸ CUỐI CÙNG: `std::views::cartesian_product` – ĐẠI TUYỆT KỸ HOÀN VŨ**  
🔥 **Tạo tất cả các cặp phần tử từ hai danh sách!**  

```cpp
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<char> b = {'A', 'B'};

    auto cartesian = std::views::cartesian_product(a, b);

    for (const auto& [num, letter] : cartesian)
        std::cout << num << " - " << letter << '\n';
}
```
💥 **Tạo tất cả các cặp `(a, b)` mà không cần hai vòng `for` lồng nhau!**  

---

🔥 **Nay ta đã truyền lại tất cả tuyệt kỹ Ranges – đạo hữu đã lĩnh hội chăng?**  
🔥 **Còn chỗ nào chưa thông suốt, hãy cứ hỏi, bần đạo sẽ khai sáng!** 🤺🔥