# Trie-prject

# Command to run out the file .exe (except main_optional.cpp): 
    g++ -std=c++11 *.cpp -o main
// this will run out the main.exe so if you you want to run this code you must: ".\main"

# Idea
~Khởi Tạo~
Build cây trie:
    +Mỗi node gồm 1 mảng lưu địa chỉ của 26 node con
    +Biến bool để xác nhận đây là kết thúc của một từ(word)

Tạo một mảng để lưu số lần xuất hiện của mỗi chữ cái trong input.Tạm gọi A

Tạo thêm mảng khác để theo dõi số lần mỗi chữ cái TRONG MẢNG INPUT đã được 
sử dụng trong quá trình DFS. Tạm gọi B

Biến count = 0, count >= 3 thì lụm, để k phải nhọc nhằn khi quay lui thì 
tui đề xuất nên truyền vào hàm tham trị của count thay gì tham chiếu

~DFS~
Với mỗi chữ cái con của nút hiện tại, nếu số lần chữ cái đó đã được sử dụng nhỏ 
hơn số lần nó xuất hiện trong danh sách đầu vào:
    +Thêm chữ cái đó vào đường đi hiện tại.
    +Tăng số lần sử dụng của chữ cái đó.
    +Tiếp tục tìm kiếm sâu từ nút con tương ứng.
    +QUAY LUI: này quan trọng xóa chữ cái khỏi đường đi hiện tại và giảm số lần 
    sử dụng của chữ cái đó.


Ví dụ: đi tới chữ 'b', nếu lần xuất hiện của 'b' trong B nhỏ hơn trong A, thì 
count tăng 1, B['b' - 'a'] tăng 1

Rồi cứ đếm vậy thoi thằng nào cho ra kq >= 3 thì lụm hết

~Tối ưu: Khi gặp một node có count >= 3 rồi thì lấy tất cả các node con của nó luôn,
khỏi phải tìm tiếp.


