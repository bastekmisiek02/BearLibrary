#pragma once

#include "Bases.h"

#include "Math/GraphicsMath/Vectors/Vectors.h"

namespace Bear
{
	class Image
	{
	public:
		using Color = GraphicsMath::Vec<char, 4>;
	public:
		struct ImageInfo
		{
			UInt width;
			UInt height;
			UInt colorDepth;
			UInt colorType;
			UInt compressionMethod;
			UInt filterMethod;
			UInt interfaceMethod;
		};
	private:
		ImageInfo imageInfo;
		Color* data;
	public:
		Image(const char* path);
		~Image();
	public:
		const Color* const GetData() const;
		ImageInfo GetImageInfo() const;
	public:
		void SaveToFile(const char* path);
	};
}