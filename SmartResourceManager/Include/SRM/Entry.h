#pragma once

#include "Resource.h"
#include "Common.h"

namespace srm
{
	// Entity is the name, size and offset of a single file in the data-file.
	class SRM_API Entry
	{
	public:
		Entry() = default;
		Entry(const String& location, const size_t size, const size_t offset);

		virtual ~Entry() = default;

		void SetLocation(const String& location);
		void SetSize(const size_t size);
		void SetOffset(const size_t offset);

		const String& GetLocation() const;
		String GetExtension() const;
		size_t GetSize() const;
		size_t GetOffset() const;

	protected:
		String location{ "" };
		size_t size{ 0 };
		size_t offset{ 0 };
	};

	void LoadAsset(Resource& resource, const String& archivePath, const Entry& entry);
}