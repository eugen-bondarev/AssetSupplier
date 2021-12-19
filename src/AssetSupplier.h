#pragma once

#include "Package.h"
#include "Common.h"
#include "Asset.h"

#define ASU_DEFAULT_EXTENSION ".asu"

namespace Asu
{
	using AssetSupplierFlags = Flags;

	// Todo: make enum class out of these enum flags.
	enum AssetSupplierFlags_
	{
		AssetSupplierFlags_None   = 1 << 0,
		AssetSupplierFlags_Create = 1 << 1,
		AssetSupplierFlags_Watch  = 1 << 2,
	};

	// Helper class for the user.
	class AssetSupplier
	{
		friend class FileChangeListener;

		inline static const String defaultTableName = "table" ASU_DEFAULT_EXTENSION;
		inline static const String defaultDataName = "data" ASU_DEFAULT_EXTENSION;

	public:
		AssetSupplier(
			const String& root,
			const String& tableFileName = defaultTableName, 
			const String& dataFileName = defaultDataName, 
			const AssetSupplierFlags flags = AssetSupplierFlags_None
		);

		bool IsFileIgnored(const String& fileName) const;

		Asset Load(const String& location);

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