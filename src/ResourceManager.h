#pragma once

#include "Resource.h"
#include "Package.h"
#include "Common.h"

#define SRM_DEFAULT_EXTENSION ".srm"

namespace srm
{
	// Helper class for the user.
	class ResourceManager
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