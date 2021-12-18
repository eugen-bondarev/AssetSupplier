#include "Entry.h"

#include <fstream>

namespace Asu
{
	Entry::Entry(const String& location, const size_t size, const size_t offset) : location{ location }, size{ size }, offset{ offset }
	{
		ASU_INFO("File: {0}, size: {1} b, offset: {2} b", location, size, offset);
	}

	void Entry::SetLocation(const String& location)
	{
		this->location = location;
	}

	void Entry::SetSize(const size_t size)
	{
		this->size = size;
	}

	void Entry::SetOffset(const size_t offset)
	{
		this->offset = offset;
	}

	const String& Entry::GetLocation() const
	{
		return location;
	}

	String Entry::GetExtension() const
	{
		const size_t lastDot{ location.find_last_of(".") };
		const String extension{ location.substr(lastDot + 1, location.size() - lastDot) };
		return extension;
	}

	size_t Entry::GetSize() const
	{
		return size;
	}

	size_t Entry::GetOffset() const
	{
		return offset;
	}

	void LoadAsset(Asset& asset, const String& archivePath, const Entry& entry)
	{
		asset.data.resize(entry.GetSize());

		std::ifstream inputStream{ archivePath, std::ios::binary };
		inputStream.seekg(entry.GetOffset());
		inputStream.read(asset.data.data(), entry.GetSize());
	}
}