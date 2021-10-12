# 3-DOF_ROBOT

Project 3-DOF_ROBOT điều khiển cánh tay robot 3 bậc tự do ứng dụng các thuật toán tính động học thuận (FK), động học nghịch (IK).

-Dùng 1 module ESP8266 và 4 module Arduino UNO, các module này sẽ giao tiếp với nhau qua giao thức I2C. 

  +4 Arduino UNO được phân chia thành các tên UNO 0, UNO 1, UNO 2, UNO 3

  +ESP8266 đóng vai trò là master của UNO 0, đây là module trao đổi dữ liệu với UNO 0 đồng thời thông qua giao thức MQTT kết nối đến giao diện điều khiển Node-RED.

  +UNO 0 đồng thời vừa là slave của ESP8266 vừa là master của UNO 1, UNO 2, UNO 3. UNO 0 tính toán các thuật toán tính động học thuận (FK), động học nghịch (IK) để trả kết quả các góc quay cho 3 UNO slaves.

  +UNO 1, UNO 2, UNO 3 nhận các góc quay từ UNO 0 để điều khiển các động cơ bước giúp cách tay robot được di chuyển một cách chính xác và mượt hơn.

Cánh tay robot có thể điều khiển đến những vị trí mong muốn (nằm trong vùng làm việc), quy hoạch quỹ đạo giúp các khớp của robot hoạt động trong cùng 1 thời gian và hoạt động êm, mượt hơn.
