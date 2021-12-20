#include <SRM/SRM.h>

#include <algorithm>

#ifndef EXAMPLE_ROOT_DIR
#	define EXAMPLE_ROOT_DIR
#endif

namespace srm
{
	class ModelAsset
	{
	public:
		ModelAsset(const srm::Resource& resource)
		{
		}
	};
}

namespace srm
{
	bool CaseInsensitiveCompareLess(const String& a, const String& b)
	{
		return std::lexicographical_compare(
			std::begin(a), std::end(a),
			std::begin(b), std::end(b),
			[](const char& aChar, const char& bChar)
			{
				return std::tolower(aChar) < std::tolower(bChar);
			}
		);
	}

	bool CaseInsensitiveCompareGreater(const String& a, const String& b)
	{
		return std::lexicographical_compare(
			std::begin(a), std::end(a),
			std::begin(b), std::end(b),
			[](const char& aChar, const char& bChar)
			{
				return std::tolower(aChar) > std::tolower(bChar);
			}
		);
	}

	void Sort(Vec<String>& vector)
	{
		std::sort(
			std::begin(vector),
			std::end(vector),
			[](const String& a, const String& b)
			{
				return CaseInsensitiveCompareLess(a, b);
			}
		);
	}

	size_t IndexOf(const Vec<String>& vector, const String& item)
	{
		size_t currentIndex{ vector.size() / 2 };

		while (vector[currentIndex] != item)
		{
			SRM_CONSOLE_INFO("%i", currentIndex);

			//const bool grt{ CaseInsensitiveCompareGreater(vector[currentIndex], item) };
			//const bool lss{ CaseInsensitiveCompareLess(vector[currentIndex], item) };
			const bool grt{ vector[currentIndex] > item };
			const bool lss{ vector[currentIndex] < item };

			if (grt)
			{
				const size_t change{ static_cast<size_t>(floorf(static_cast<float>(currentIndex) / 2)) };
				currentIndex -= change;
			}
			else if (lss)
			{
				const size_t change{ static_cast<size_t>(floorf(static_cast<float>(vector.size() - currentIndex) / 2)) };
				currentIndex += change;
			}
		}

		return currentIndex;
	}

	void Print(const Vec<String>& vector)
	{
		for (const String& item : vector)
		{
			SRM_CONSOLE_INFO(item);
		}
	}

	void Test()
	{
		Vec<String> testVector = {
			"a",
			"aa",
			"AA",
			"aaB",
			"aAB",
			"Aab",
			"ab",
			"aBA",
			"aBAA",
		};

		const size_t i{ IndexOf(testVector, testVector[2])};
		SRM_CONSOLE_INFO("%i", i);
	}
}

int main(const int argc, const char* argv[])
{
	srm::Test();
	return 0;

	const srm::String root{ EXAMPLE_ROOT_DIR "/Assets" };

	srm::ResourceManager resourceManager{ root, "table.asu", "data.asu", srm::ResourceManager::Mode::Create };
	srm::Resource resource;

	struct MyModelAsset
	{
		MyModelAsset(const srm::Resource& resource)
		{
			SRM_CONSOLE_INFO("Calling constructor model");
		}
	};

	struct MyImageAsset
	{
		MyImageAsset(const srm::Resource& resource)
		{
			SRM_CONSOLE_INFO("Calling constructor image");
		}
	};

	srm::Cache<MyModelAsset> modelCache(resourceManager);
	srm::Cache<MyImageAsset> imageCache(resourceManager);

	const MyModelAsset& model0 = modelCache.Load("a/b/ddc");
	const MyModelAsset& model1 = modelCache.Load("a/b/ddc");
	const MyImageAsset& image0 = imageCache.Load("a/b/OtherShader.frag");
	const MyImageAsset& image1 = imageCache.Load("a/b/OtherShader.frag");

	try
	{
		resource = resourceManager.Load("a/b/ddc");
	}
	catch (const srm::Exception& exception)
	{
		SRM_CONSOLE_OUT("[Error] %s", exception.what());
	}

	if (resource)
	{
		srm::String str{ "" };
		for (size_t i = 0; i < resource.data.size(); ++i)
		{
			str += resource.data[i];
		}
		SRM_CONSOLE_INFO(str);
	}

	return 0;
}