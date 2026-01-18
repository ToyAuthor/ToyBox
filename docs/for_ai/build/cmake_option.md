# CMake選項
本文件說明`ToyBox`在CMake設定檔上面設計了哪些選項

## 原生選項
在根目錄的`ToyBox/CMakeLists.txt`文件上面有一行寫著：
```cmake
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
```
這是用來決定這個專案要用Debug還是Release選項來編譯，
但是並非在所有環境下都成立，例如Visual Studio就無法這樣控制。

## `ToyBox`選項
這些選項寫在`ToyBox/cmake/toy_Option.cmake`上面，
就是這種CMake語法：
```cmake
option(TOY_ENABLE_SHARED_LIBS "Make shared library" ON)
```
|Option|Commit|
|:----------|:----------|
|TOY_ENABLE_SHARED_LIBS|決定是否編譯成動態函式庫，現在總是勾選，因為目前無法編譯成靜態函式庫|
|TOY_ENABLE_ALPHA_API|可用這個選項啟用那些尚在嘗試中的介面|
|TOY_ENABLE_MAY_REMOVED|可用這個選項啟用那些未來即將棄用的介面|
