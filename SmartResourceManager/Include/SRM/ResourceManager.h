#pragma once

#include "EntryTable.h"
#include "Resource.h"
#include "Common.h"
#include "Entry.h"

#define SRM_DEFAULT_EXTENSION ".srm"

namespace srm
{
	void AssetsToFile(const String& path, const String& pathPrefix, const EntryTable& entryList);

	// Helper class for the user.
	class SRM_API ResourceManager
	{
		friend class FileChangeListener;

		inline static const String defaultTableName = "table" SRM_DEFAULT_EXTENSION;
		inline static const String defaultDataName = "data" SRM_DEFAULT_EXTENSION;

	public:
		enum class Mode
		{
			Default = 0,
			Create,
			Watch
		};

		ResourceManager(
			const String& root,
			const String& tableFileName = defaultTableName, 
			const String& dataFileName = defaultDataName, 
			const Mode mode = Mode::Default
		);

		bool IsFileIgnored(const String& fileName) const;

		Resource Load(const String& location);

	private:
		void OnFlagCreate();
		void OnFlagNone();

		const Entry& FindEntry(const String& location);

		String tableFileName;
		String dataFileName;

		String root;
		EntryTable table;

		Vec<String> ignoreFiles;
	};
}