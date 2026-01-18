# Component介紹
這裡會介紹`ToyBox`內部各個重要的C++ component

## 前言
放在`ToyBox/include/toy`裡面的絕大部份標頭檔都是一個component，它們都有自己的功用與目標，
`ToyBox`的所有標頭檔都統一使用「hpp」來當副檔名，
如果有數個component是聯合為了共同目標而建立，那麼該目標也會有一個自己的標頭檔作為代表。

AI跟人類都可以閱讀`ToyBox/examples/usage`這個資料夾來尋找範例程式碼，
這裡先用`ToyBox/include/toy/ImageBuffer.hpp`來舉例，
在C++程式碼當中會這樣引用並宣告該物件：
```cpp
#include <toy/ImageBuffer.hpp>;
static ::toy::ImageBuffer buffer;
```
所以資料夾結構是符合name space的，
如果想要看ImageBuffer的使用範例，就去看`ToyBox/examples/usage/ToyBox/include/toy/ImageBuffer.hpp`這份文件，
該文件副檔名也是「hpp」，但是內容並非標頭檔，而是使用範例，
故意將檔名設計的這麼相似，是為了方便使用者去尋找對應的範例程式碼。

## 重要的Component們
以下統一以標頭檔為單位來介紹component。

### `ToyBox/include/toy/Log.hpp`
這個是負責印出訊息用的，只允許輸入UTF-8字串。
> 需要`toy.lib`

### `ToyBox/include/toy/File.hpp`
用來讀取檔案資料，讀取圖片之類的檔案可以靠它，
支援從`zip`跟`7zip`格式的壓縮檔裡面讀取檔案，
因為假定了檔案全都是2G以下的大小，因此才會用 uint32_t 來計算檔案大小，
相關的公開標頭檔都放在`ToyBox/include/toy/file`這個資料夾裡面，
其中最核心的類別是這個`ToyBox/include/toy/file/File.hpp`。
> 需要`toy_file.lib`

### `ToyBox/include/toy/Photo.hpp`
相關的公開標頭檔都放在`ToyBox/include/toy/photo`這個資料夾裡面，
工作上都圍繞著`ToyBox/include/toy/ImageBuffer.hpp`這個類別，此類別提供一個名為`::toy::ImageBuffer`的容器，
`::toy::ImageBuffer`用來裝圖片資料，而`ToyBox/include/toy/photo`這個資料夾裡面提供了各種圖片修改工具，
例如裁減圖片、拼裝圖片、改變圖片色調。
> 需要`toy_photo.lib`

### `ToyBox/include/toy/Path.hpp`
這個基本上就是`boost::filesystem`的再包裝。
> 需要`toy.lib`

### `ToyBox/include/toy/Font.hpp`
這個基本上就是`freetype2`的再包裝。
> 需要`toy_font.lib`

### `ToyBox/include/toy/time/Timer.hpp`
一個簡單的計時器實作，程式碼很少，直接閱讀就能理解。
> 需要`toy_time.lib`
