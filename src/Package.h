#pragma once

#include "Common.h"
#include "Entry.h"

namespace Asu
{
	void CreateEntryTable(Entries& table, const String& root);
	void EntryTableFromFile(Entries& table, const String& path);
	void EntryTableToFile(const String& path, const Entries& table);
	void AssetsToFile(const String& path, const String& pathPrefix, const Entries& tables);
}