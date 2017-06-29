#ifdef TOY_WINDOWS
#include <windows.h>
#endif

#include <cstdlib>
#include <cstring>
#include "toy/file/io/SevenZip.hpp"


using namespace toy;
using namespace file;
using namespace io;

//---------------------------Come from 7zip example---------------------------start

typedef int SRes;

static void *SzAlloc(void *p, size_t size)
{
	(void)p;
	return MyAlloc(size);
}
static void SzFree(void *p, void *address)
{
	(void)p;
	MyFree(address);
}

void *SzAllocTemp(void *p, size_t size)
{
	(void)p;
	if (size == 0)
		return 0;
	#ifdef _SZ_ALLOC_DEBUG
		fprintf(stderr, "\nAlloc_temp %10d bytes;  count = %10d", size, g_allocCountTemp);
		g_allocCountTemp++;
		#ifdef _WIN32
			return HeapAlloc(GetProcessHeap(), 0, size);
		#endif
	#endif
	return malloc(size);
}

void SzFreeTemp(void *p, void *address)
{
	(void)p;
	#ifdef _SZ_ALLOC_DEBUG
		if (address != 0)
		{
			g_allocCountTemp--;
			fprintf(stderr, "\nFree_temp; count = %10d", g_allocCountTemp);
		}
		#ifdef _WIN32
			HeapFree(GetProcessHeap(), 0, address);
			return;
		#endif
	#endif
	free(address);
}

static ISzAlloc g_Alloc = { SzAlloc, SzFree };

static int Buf_EnsureSize(CBuf *dest, size_t size)
{
	if (dest->size >= size)
		return 1;
	Buf_Free(dest, &g_Alloc);
	return Buf_Create(dest, size, &g_Alloc);
}

#if defined(TOY_LINUX) || defined(TOY_MAC) || defined(TOY_ANDROID)
static Byte kUtf8Limits[5] = { 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

static Bool Utf16_To_Utf8(Byte *dest, size_t *destLen, const UInt16 *src, size_t srcLen)
{
	size_t destPos = 0, srcPos = 0;
	for (;;)
	{
		unsigned numAdds;
		UInt32 value;
		if (srcPos == srcLen)
		{
			*destLen = destPos;
			return True;
		}
		value = src[srcPos++];
		if (value < 0x80)
		{
			if (dest)
			dest[destPos] = (char)value;
			destPos++;
			continue;
		}
		if (value >= 0xD800 && value < 0xE000)
		{
			UInt32 c2;
			if (value >= 0xDC00 || srcPos == srcLen)
				break;
			c2 = src[srcPos++];
			if (c2 < 0xDC00 || c2 >= 0xE000)
				break;
			value = (((value - 0xD800) << 10) | (c2 - 0xDC00)) + 0x10000;
		}
		for (numAdds = 1; numAdds < 5; numAdds++)
			if (value < (((UInt32)1) << (numAdds * 5 + 6)))
				break;
		if (dest)
			dest[destPos] = (char)(kUtf8Limits[numAdds - 1] + (value >> (6 * numAdds)));
		destPos++;
		do
		{
			numAdds--;
			if (dest)
				dest[destPos] = (char)(0x80 + ((value >> (6 * numAdds)) & 0x3F));
			destPos++;
		}
		while (numAdds != 0);
	}
	*destLen = destPos;
	return False;
}
static SRes Utf16_To_Utf8Buf(CBuf *dest, const UInt16 *src, size_t srcLen)
{
	size_t destLen = 0;
	Bool res;
	Utf16_To_Utf8(NULL, &destLen, src, srcLen);
	destLen += 1;
	if (!Buf_EnsureSize(dest, destLen))
		return SZ_ERROR_MEM;
	res = Utf16_To_Utf8(dest->data, &destLen, src, srcLen);
	dest->data[destLen] = 0;
	return res ? SZ_OK : SZ_ERROR_FAIL;
}
#endif
static SRes Utf16_To_Char(CBuf *buf, const UInt16 *s, int fileMode)
{
	int len = 0;
	for (len = 0; s[len] != '\0'; len++){}

	#ifdef _WIN32
		int size = len * 3 + 100;
		if (!Buf_EnsureSize(buf, size))
		{
			return SZ_ERROR_MEM;
		}

		char defaultChar = '_';
		BOOL defUsed;
		UINT codePage;

		#ifdef UNDER_CE
			codePage = fileMode ? CP_ACP : CP_OEMCP;
		#else
			codePage = fileMode ? ( AreFileApisANSI() ? CP_ACP : CP_OEMCP ) : CP_OEMCP;
		#endif

		int numChars = WideCharToMultiByte( codePage,
		                                    0,
		                                    (LPCWSTR)s,
		                                    len,
		                                    (char *)buf->data,
		                                    size,
		                                    &defaultChar,
		                                    &defUsed);

		if (numChars == 0 || numChars >= size)
		{
			return SZ_ERROR_FAIL;
		}

		buf->data[numChars] = 0;
		return SZ_OK;
	#else
		(void)fileMode;
		return Utf16_To_Utf8Buf(buf, s, len);
	#endif
}

static int SzCheckName(const char *name1,UInt16 *name2)
{
	CBuf buf;
	Buf_Init(&buf);
	Utf16_To_Char(&buf, name2, 0);
	int answer=strcmp((const char *)buf.data,name1);
	Buf_Free(&buf, &g_Alloc);

	if(answer==0)
		return 1;
	else
		return 0;
}

//---------------------------Come from 7zip example---------------------------end





SevenZip::SevenZip()
{
	_allocImp.Alloc = SzAlloc;
	_allocImp.Free = SzFree;
	_allocTempImp.Alloc = SzAllocTemp;
	_allocTempImp.Free = SzFreeTemp;
	_temp = NULL;
	_outBuffer=0;

	SzArEx_Init(&(_db));
}

bool SevenZip::openDir(std::string path)
{
	if ( InFile_Open(&(_archiveStream.file),path.c_str()) )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

	SRes res;

	FileInStream_CreateVTable(&(_archiveStream));
	LookToRead_CreateVTable(&(_lookStream), False);
	_lookStream.realStream = &(_archiveStream.s);
	LookToRead_Init(&(_lookStream));
	CrcGenerateTable();
	SzArEx_Init(&(_db));

	res = SzArEx_Open(&(_db), &(_lookStream.s), &(_allocImp), &(_allocTempImp));

	if (res != SZ_OK)
	{
		Oops(TOY_MARK);
		SzArEx_Free(&(_db), &(_allocImp));
		SzFree(NULL, _temp);
		File_Close(&(_archiveStream.file));
		return 0;
	}

	return 1;
}

bool SevenZip::open(std::string filepath)
{
	size_t	len;
	size_t	tempSize = 0;
	SRes	res;
	UInt32	blockIndex = 0xFFFFFFFF;
	size_t	outBufferSize = 0;
	size_t	offset = 0;
	size_t	outSizeProcessed = 0;

	UInt32	i=0;
	UInt32	number_of_files=_db.db.NumFiles;

	for ( ; i<number_of_files ; i++ )
	{
		const CSzFileItem *f = _db.db.Files + i;

		if ( f->IsDir )
		{
			continue;
		}

		len = SzArEx_GetFileNameUtf16(&(_db), i, NULL);

		if ( len > tempSize )
		{
			SzFree(NULL, _temp);
			tempSize = len;
			_temp = (UInt16 *)SzAlloc(NULL, tempSize * sizeof(_temp[0]));
			if ( _temp == 0 )
			{
				toy::Oops(TOY_MARK);
				return 0;
			}
		}

		SzArEx_GetFileNameUtf16(&(_db), i, _temp);

		if ( SzCheckName(filepath.c_str(),_temp) )
		{
			res = SzArEx_Extract(&(_db), &(_lookStream.s), i,
			&blockIndex, &(_outBuffer), &outBufferSize,
			&offset, &outSizeProcessed,
			&(_allocImp), &(_allocTempImp));
			if(res == SZ_OK)
			{
				_fileSize = outSizeProcessed;
				_fileBegin = (void*)((_outBuffer)+offset);
				return 1;
			}
			else
			{
				toy::Oops(TOY_MARK);
				_fileSize = 0;
				_fileBegin = nullptr;
				return 0;
			}
		}
	}

	toy::Oops(TOY_MARK);

	_fileSize = 0;
	_fileBegin = nullptr;
	return 0;
}

uint32_t SevenZip::read(void *file, uint32_t size)
{
	auto   data = static_cast<Byte*>(_fileBegin);

	if ( _fileSize < size+_passSize )
	{
		size = _fileSize-_passSize;
	}

	memcpy(file,data+_passSize,size);

	_passSize+=size;

	return size;
}

bool SevenZip::write(void *,uint32_t )
{
	// Not ready yet
	toy::Oops(TOY_MARK);
	return 1;
}

static int32_t SeekSET(int32_t offset,int32_t total)
{
	if ( offset > total )
	{
		// Too big.
		toy::Oops(TOY_MARK);
		offset = total;      // Move to the end of file.
	}
	else if ( offset<0 )
	{
		// It should always bigger than zero.
		toy::Oops(TOY_MARK);
		offset = 0;          // Move to the beginning of file.
	}

	return offset;
}

static int32_t SeekEND(int32_t offset,int32_t total)
{
	if ( offset < total*-1 )
	{
		// Too big.
		toy::Oops(TOY_MARK);
		offset = total*-1;   // Move to the beginning of file.
	}
	else if ( offset>0 )
	{
		// It should always bigger than zero.
		toy::Oops(TOY_MARK);
		offset = 0;          // Move to the end of file.
	}

	return total + offset;
}

static int32_t SeekCUR(int32_t offset,int32_t total,int32_t pass)
{
	if ( offset>0 )
	{
		if ( offset+pass>total )
		{
			offset = total - pass;  // Move to the end of file.
		}
	}
	else if ( offset<0 )
	{
		if ( offset*-1>pass )
		{
			offset = pass*-1;       // Move to the beginning of file.
		}
	}

	return pass + offset;
}

bool SevenZip::seek(int option,int32_t offset)
{
	if ( isEmpty() ) return 0;

	switch (option)
	{
		case SEEK_SET:
			_passSize = SeekSET(offset,_fileSize);
			break;
		case SEEK_END:
			_passSize = SeekEND(offset,_fileSize);
			break;
		case SEEK_CUR:
			_passSize = SeekCUR(offset,_fileSize,_passSize);
			break;
		default:
			toy::Oops(TOY_MARK);
			_passSize = SeekCUR(offset,_fileSize,_passSize);
			break;
	}

	return 1;
}

void SevenZip::close()
{
	IAlloc_Free(&(_allocImp), _outBuffer);

	SzArEx_Free(&(_db), &(_allocImp));

	if ( _temp )
	{
		SzFree(NULL, _temp);
		_temp=NULL;
	}
	File_Close(&(_archiveStream.file));

	_passSize = 0;
}

bool SevenZip::isEmpty()
{
	return 1;
}

bool SevenZip::isEnd()
{
	if ( _passSize == _fileSize )
	{
		return 1;
	}

	return 0;
}
