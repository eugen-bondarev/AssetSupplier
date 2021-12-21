#pragma once

#include "EntryTable.h"
#include "Resource.h"
#include "Common.h"
#include "Entry.h"

#define SRM_DEFAULT_EXTENSION ".srm"

namespace srm
{
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

		virtual ~ResourceManager() = default;

		bool IsFileIgnored(const String& fileName) const;

		// This isn't cached by default, but you can set up a cache.
		Resource Load(const String& location);

	protected:
		void OnFlagCreate();
		void OnFlagNone();

		const Entry& FindEntry(const String& location);

		String tableFileName;
		String dataFileName;

		String root;
		EntryTable entryTable;

		Vec<String> ignoreFiles;
	};
}