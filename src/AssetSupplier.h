#pragma once

#include "Package.h"
#include "Common.h"
#include "Asset.h"

namespace Asu
{
	using AssetSupplierFlags = Flags;

	enum AssetSupplierFlags_
	{
		AssetSupplierFlags_None   = 1 << 0,
		AssetSupplierFlags_Create = 1 << 1,
		AssetSupplierFlags_Watch  = 1 << 2,
	};

	// Helper class for the user.
	class AssetSupplier
	{
		friend class AsuListener;

	public:
		AssetSupplier(const String& root, const AssetSupplierFlags flags = AssetSupplierFlags_None);

		Asset Load(const String& location);

	private:
		void OnFlagCreate();
		void OnFlagNone();

		const Entry& FindEntry(const String& location);

		String root;
		EntryTable table;
	};
}