#include "Image.h"

#include <fstream>

#include "Collections/String/String.h"
#include "Math/Math/Math.h"

namespace Bear
{
	static inline void Getline(UChar* data, UChar* dst, const ULInt& size, ULInt& index)
	{
		ULInt i = 0;
		while (data[index] != '\n' && index != size)
		{
			dst[i] = data[index];

			index++;
			i++;
		}

		dst[i] = '\0';
		index++;
	}

	static const ULInt GetInt(UChar* data, ULInt& index)
	{
		UChar numberChar[20];

		for (ULInt i = 0; i < 20; i++)
		{
			if (data[index] == ' ' || data[index] == '\n')
			{
				numberChar[i] = '\0';
				index++;
				return Collections::String::ConvertTo<ULInt>((char*)numberChar);
			}
			else
			{
				numberChar[i] = data[index];
				index++;
			}
		}
	}

	#define THROW throw "error"

	Image::Image(const char* path)
		: imageInfo({0, 0, 0, 0, 0, 0, 0}), data(nullptr)
	{
		ULInt fileSize = 0;

		UChar* fileData = nullptr;

		std::ifstream file(path, std::ios::binary | std::ios::ate);
		{
			if (file)
			{
				fileSize = file.tellg();

				fileData = new UChar[fileSize];

				if (file.is_open() && !file.bad() && file.good() && !file.fail())
				{
					file.seekg(0);
					file.read((char*)fileData, fileSize);
				}
				else
					throw "Something is wrong with file";

				file.close();
			}
			else
				throw "File doesn't exists";
		}

		ULInt index = 0;
		UChar dst[1024];

		Getline(fileData, dst, fileSize, index);

		if (Collections::String::Compare((char*)dst, "P6"))
		{
			int bpp;

			while (true)
			{
				if (fileData[index] == '#')
					Getline(fileData, dst, fileSize, index);
				else
					break;
			}

			imageInfo.width = GetInt(fileData, index);
			imageInfo.height = GetInt(fileData, index);
			bpp = GetInt(fileData, index);
			
			this->data = new Color[imageInfo.width * imageInfo.height];

			for (UInt i = 0; i < imageInfo.width * imageInfo.height; i++)
			{				
				this->data[i].r = fileData[index++];
				this->data[i].g = fileData[index++];
				this->data[i].b = fileData[index++];
				this->data[i].a = 255;
			}
		}
		else if (Collections::String::Compare((char*)dst, "‰PNG\r"))
		{
			//TODO: Po zrozumieniu jak dzia³a odkodowanie IDAT zrobiæ tu od pocz¹tku ¿eby dok³adnie wszystko zakomentowaæ gdzie trzeba (¿e np. compress method tu siê zmienia itp.) i dok³adnie wszystkie wyj¹tki wyrzucaæ
			bool dataRead = false;
			bool PLTE_chunkRead = false;

			index += 2;

			while (index < fileSize)
			{
				UInt size = 0;

				for (int i = 4; i > 0; i--)
					size += (Math::Pow<UInt>(16, 2 * (i - 1)) * fileData[index++]);

				char name[5];
				{
					for (char i = 0; i < 4; i++)
						name[i] = fileData[index++];
				}
				name[4] = '\0';

				if (Collections::String::Compare(name, "IHDR"))
				{
					for (char i = 4; i > 0; i--)
						imageInfo.width += (Math::Pow(16, 2 * (i - 1)) * fileData[index++]);

					for (char i = 4; i > 0; i--)
						imageInfo.height += (Math::Pow(16, 2 * (i - 1)) * fileData[index++]);

					imageInfo.colorDepth = fileData[index++];
					imageInfo.colorType = fileData[index++];
					imageInfo.compressionMethod = fileData[index++];
					imageInfo.filterMethod = fileData[index++];
					imageInfo.interfaceMethod = fileData[index++];

					if (imageInfo.compressionMethod != 0 || imageInfo.filterMethod != 0 || (imageInfo.interfaceMethod != 0 && imageInfo.interfaceMethod != 1))
						throw "Get an unrecognized code";
				}
				else if (Collections::String::Compare(name, "PLTE"))
				{
					{
						if (PLTE_chunkRead)
							THROW;

						if (dataRead)
							THROW;

						if (size % 3 != 0)
							THROW;

						if (imageInfo.colorType == 0 || imageInfo.colorType == 4)
							THROW;
					}

					if (imageInfo.colorType == 3)
					{
						for (UInt i = 0; i < Math::Pow<UInt>(2, imageInfo.colorDepth); i++)
						{
							if (fileData[index++] != i)
								THROW;
						}
					}

					PLTE_chunkRead = true;
				}
				else if (Collections::String::Compare(name, "IDAT"))
				{
					//TODO: Zrobiæ to teraz
					//TODO: Dodaæ zlib decompresjê

					if (imageInfo.colorType == 3 && !PLTE_chunkRead)
						THROW;

					//UChar compressedType[2] = { bits[0], bits[1] };
					ULInt scanLineSize = imageInfo.width * 4 + 1;

					data = new Color[imageInfo.width * imageInfo.height];

					for (UInt i = 0; i < imageInfo.height; i++)
					{
						//UChar filterType = fileData[index++];//bits[i * scanLineSize];

						//for (ULInt j = 0; j < scanLineSize; j++)
						//{
						//	data[i * j].r;
						//}
					}

					index += size;

					dataRead = true;
				}
				else
					index += size;

				UInt checksum = 0;
				{
					for (char i = 4; i > 0; i--)
						checksum += (Math::Pow(16, 2 * (i - 1)) * fileData[index++]);
				}

				//TUTAJ: Sprawdziæ tutaj czy zgadza siê suma kontrolna
			}

			delete[] fileData;
		}
	}

	Image::~Image()
	{
		delete[] data;
	}

	Image::ImageInfo Image::GetImageInfo() const
	{
		return imageInfo;
	}

	Image::Color* Image::GetData() const
	{
		return data;
	}

	void Image::SaveToFile(const char* path)
	{
		std::ofstream file(path, std::ios::binary);
		{
			if (file.is_open())
			{
				std::string header = "P6\n";

				file << header;
				file << imageInfo.width << " " << imageInfo.height << " " << "\n255\n";

				for (UInt i = 0; i < imageInfo.width * imageInfo.height; i++)
					file.write((const char*)&data[i], 3);

				file.close();
			}
		}
	}
}