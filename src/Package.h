#pragma once

#include "Common.h"
#include "Entry.h"

namespace Asu
{
	void CreateEntryTable(EntryTable& table, const String& root, const Vec<String>& ignoreFiles = {});
	void EntryTableFromFile(EntryTable& table, const String& path);
	void EntryTableToFile(const String& path, const EntryTable& table);
	void AssetsToFile(const String& path, const String& pathPrefix, const EntryTable& tables);
}