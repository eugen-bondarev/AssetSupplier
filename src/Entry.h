#pragma once

#include "Common.h"
#include "Asset.h"

namespace Asu
{
	class Entry
	{
	public:
		Entry() = default;
		Entry(const String& location, const size_t size, const size_t offset);

		void SetLocation(const String& location);
		void SetSize(const size_t size);
		void SetOffset(const size_t offset);

		const String& GetLocation() const;
		String GetExtension() const;
		size_t GetSize() const;
		size_t GetOffset() const;

	private:
		String location{ "" };
		size_t size{ 0 };
		size_t offset{ 0 };
	};

	using EntryTable = Vec<Entry>;

	void LoadAsset(Asset& asset, const String& archivePath, const Entry& entry);
}