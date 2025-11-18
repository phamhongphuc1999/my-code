## Báo cáo cấu trúc một dự án project

### Tổng quan

- Dự án sử dụng nestjs để tạo một API kết nối đến cơ sở dữ liệu mysql, thực hiện đọc ghi dữ liệu vào database
- Cấu trúc của dự án bao gồm

```shell
REQUEST --> MIDDLEWARE --> GUARDS --> INTERCEPTORS --> PIPES --> CONTROLLER --> SERVICE
```

#### Request:

- Yêu cầu từ client (trình duyệt, ứng dụng di động) đến server NestJS.

#### MIDDLEWARE:

- Phần trung gian, ví dụ logging, CORS, headers.

#### GUARDS

- Bộ bảo vệ, thực thi trước khi controller được tìm thấy, ví dụ như Authorization hoặc Authentication.

#### INTERCEPTORS

- Được chạy trước khi Route Handler (phương thức trong Controller) được gọi.

#### PIPES

- Ngay trước khi tham số được truyền vào Controller, ví dụ Transformation và xác thực dữ liệu đầu vào.

#### CONTROLLER

- Phần chính chạy logic của Router handler, nhận tham số đã được xử lý, sau đó gọi phương thức tương ứng trong Service.

#### SERVICE

- Thực thi logic nghiệp vụ cốt lõi và tương tác với tầng dữ liệu (Repository).

### Kết nối với cơ sở dữ liệu

- Dự án có kết nối đến mysql (sử dụng docker để tạo database), được cấu hình trong [app.module.ts](../src/app.module.ts). Cụ thể, app module sử dụng import để sử dụng danh sách các module mà AppModule cần kết nối và sử dụng.

### Unit test

- Dự án sử dụng jest để tạo unit test ([users.controller.spec.ts](../src/app.controller.spec.ts)), file này sẽ chỉ test user controller bằng cách mock dữ liệu UserService chứ không truy cập vào database thực tế. Cụ thể, file sẽ
  - Tạo dữ liệu giả lập (mockUser, mock DTO).
  - Tạo mock service với tất cả các method controller sử dụng.
  - Tạo TestingModule để inject controller và mock service.
  - Gọi các phương thức controller trong các test case, so sánh kết quả với mock data.
  - Đảm bảo service được gọi đúng với đúng argument và số lần gọi.
  - Xử lý các tình huống ngoại lệ như NotFoundException.
