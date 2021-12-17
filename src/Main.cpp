#include "Package.h"

// AssetManager = 
//		data0.asu, data1.asu, dataN.asu
// +
//		descriptor
//		Entry example:
// 
//		Assets/Models/Humanoid/Orc.fbx 5000000
//		GetLocation() const : string = "Assets/Models/Humanoid"
//		GetExtension() const: string = "fbx" -> Helps us find the corresponding importer
//		GetSize() const : size_t = 5000000

int main()
{
	spdlog::set_pattern("[%^%l%$] %v");
	Asu::Package package("C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets");

	return 0;
}