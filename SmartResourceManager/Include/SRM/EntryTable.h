#pragma once

#include "Common.h"
#include "Entry.h"

namespace srm
{
	class SRM_API EntryTable
	{
		friend class ResourceManager;

		friend static void AppendToEntryTable(
			EntryTable& table,
			const String& root,
			const String& pathWithMessySlashes,
			size_t& offset,
			const Vec<String>& ignoreFiles
		);

	public:
		EntryTable() = default;
		virtual ~EntryTable() = default;

		void Load(const String& path);
		void Create(const String& root, const Vec<String>& ignoreFiles);

		void CreateTableFile(const String& path);
		void CreateDataFile(const String& path, const String& pathPrefix);

		void SortAlphabetically();
		void SortByOffset();

	protected:
		Vec<Entry> entries;
	};
}