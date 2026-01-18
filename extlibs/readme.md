# Third-Party Libraries
To keep the ToyBox project directory lightweight,
only compact third-party libraries are included in the directory.
Other required third-party dependencies are not bundled.

For the included libraries, non-essential files are removed to reduce size,
while the source code itself remains unmodified to comply with their respective licenses.


## Documents
Please see `ToyBox/license`.


## Internal Libraries
|Name         |Version       |License      |
|:------------|:-------------|:------------|
|**7-Zip**    |9.20          |LGPL-2.1     |
|**P7zip**    |9.20.1        |LGPL-2.1     |
|**GLEW**     |1.11.0        |BSD          |
|**GLM**      |0.9.5.4       |MIT          |
|**Linenoise**|1.0.1         |BSD          |
|**Lua**      |5.4.0         |MIT          |
|**luapp**    |2.5.0         |MIT          |
|**LZ4**      |1.8.0         |BSD          |
|**mio**      |`git:8b6b7d87`|MIT          |
|**SQLite**   |3.28.0        |Public Domain|
|**stb_image**|2.16          |Public Domain|
|**zlib**     |1.2.8         |Zlib         |

> **Note:**
> |Name          |Note                                                          |
> |:-------------|:-------------------------------------------------------------|
> |**Linenoise:**|linenoise-ng(Linenoise Next Generation)                       |
> |**mio:**      |Full git commit ID: `8b6b7d878c89e81614d05edca7936de41ccdd2da`|
> |**stb_image:**|Part of the `stb` single-file libraries.                      |


## External Dependencies
|Name        |Version|License    |
|:-----------|:------|:----------|
|**Boost**   |1.60.0 |BSL-1.0    |
|**FLTK**    |1.4.4  |LGPL-2.0   |
|**FreeType**|2.5.3  |FTL/GPL-2.0|
|**GMP**     |6.1.2  |LGPL-3.0   |
|**MPIR**    |3.0.0  |LGPL-3.0   |
|**libwebp** |1.0.2  |BSD        |
|**SFML**    |2.3.2  |Zlib       |


## Usage
Refer to `ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`
for the expected layout and configuration of third-party libraries.
