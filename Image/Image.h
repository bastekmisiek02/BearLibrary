#pragma once

#include "Bases.h"

#include "Math/GraphicsMath/Vectors/Vectors.h"

namespace Bear
{
	namespace Image
	{
		using Color = GraphicsMath::Vec<UChar, 4>;

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

		class Image
		{
		private:
			ImageInfo imageInfo;
			Color* data;
		public:
			Image(const char* path);
			~Image();
		public:
			Color* GetData() const;
			ImageInfo GetImageInfo() const;
		public:
			void SaveToFile(const char* path);
		};
	}
}