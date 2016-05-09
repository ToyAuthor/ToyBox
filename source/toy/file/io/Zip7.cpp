#ifdef TOY_WINDOWS
#include <windows.h>
#endif

#include <cstdlib>
#include <cstring>
#include "toy/file/io/Zip7.hpp"



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
#if defined(TOY_LINUX) || defined(TOY_MAC)
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





Zip7::Zip7()
{
	this->allocImp.Alloc = SzAlloc;
	this->allocImp.Free = SzFree;
	this->allocTempImp.Alloc = SzAllocTemp;
	this->allocTempImp.Free = SzFreeTemp;
	this->temp = NULL;
	this->outBuffer=0;

	SzArEx_Init(&(this->db));
}

bool Zip7::OpenDir(std::string path)
{
	if(InFile_Open(&(this->archiveStream.file),path.c_str()))
	{
		Oops(TOY_MARK);
		return 0;
	}

	SRes res;

	FileInStream_CreateVTable(&(this->archiveStream));
	LookToRead_CreateVTable(&(this->lookStream), False);
	this->lookStream.realStream = &(this->archiveStream.s);
	LookToRead_Init(&(this->lookStream));
	CrcGenerateTable();
	SzArEx_Init(&(this->db));

	res = SzArEx_Open(&(this->db), &(this->lookStream.s), &(this->allocImp), &(this->allocTempImp));

	if (res != SZ_OK)
	{
		Oops(TOY_MARK);
		SzArEx_Free(&(this->db), &(this->allocImp));
		SzFree(NULL, this->temp);
		File_Close(&(this->archiveStream.file));
		return 0;
	}

	return 1;
}

bool Zip7::Open(std::string filepath)
{
	size_t	len;
	size_t	tempSize = 0;
	SRes	res;
	UInt32	blockIndex = 0xFFFFFFFF;
	size_t	outBufferSize = 0;
	size_t	offset = 0;
	size_t	outSizeProcessed = 0;

	UInt32	i=0;
	UInt32	number_of_files=this->db.db.NumFiles;
	for (;i<number_of_files;i++)
	{
		const CSzFileItem *f = this->db.db.Files + i;

		if(f->IsDir)
		{
			continue;
		}

		len=SzArEx_GetFileNameUtf16(&(this->db), i, NULL);

		if(len > tempSize)
		{
			SzFree(NULL, this->temp);
			tempSize = len;
			this->temp = (UInt16 *)SzAlloc(NULL, tempSize * sizeof(this->temp[0]));
			if(this->temp == 0)
			{
				Oops(TOY_MARK);
				return 0;
			}
		}

		SzArEx_GetFileNameUtf16(&(this->db), i, this->temp);

		if(SzCheckName(filepath.c_str(),this->temp))
		{
			res = SzArEx_Extract(&(this->db), &(this->lookStream.s), i,
			&blockIndex, &(this->outBuffer), &outBufferSize,
			&offset, &outSizeProcessed,
			&(this->allocImp), &(this->allocTempImp));
			if(res == SZ_OK)
			{
				mFileSize=outSizeProcessed;
				mFilePointer=(void*)((this->outBuffer)+offset);
				return 1;
			}
			else
			{
				Oops(TOY_MARK);
				mFileSize=0;
				mFilePointer=0;
				return 0;
			}
		}
	}

	Oops(TOY_MARK);

	mFileSize=0;
	mFilePointer=0;
	return 0;
}

bool Zip7::Read(void *file, uint32_t size)
{
	if(mFileSize<size)
	{
		Oops(TOY_MARK);
		return 0;
	}

	Byte  *data=(Byte*)mFilePointer;

	memcpy(file,mFilePointer,size);

	data+=size;

	mFilePointer=(void*)data;

	return 1;
}

bool Zip7::Write(void *,uint32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return 1;
}
bool Zip7::Seek(enum Base::Option ,int32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return 1;
}
void Zip7::Close()
{
	IAlloc_Free(&(this->allocImp), this->outBuffer);

	SzArEx_Free(&(this->db), &(this->allocImp));

	if(this->temp)
	{
		SzFree(NULL, this->temp);
		this->temp=NULL;
	}
	File_Close(&(this->archiveStream.file));
}
bool Zip7::IsEmpty()
{
	return 1;
}
void* Zip7::GetFilePointer()
{
	// There is no way to do it.
	Oops(TOY_MARK);
	return nullptr;
}
