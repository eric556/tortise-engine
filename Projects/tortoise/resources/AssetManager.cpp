#include "AssetManager.h"

using namespace tortoise::asset;

template <class T>
void AssetManager<T>::addAsset(const std::string& id, std::shared_ptr<T> asset) {
	if (assetMap.find(id) == assetMap.end()) {
		assetMap[id] = asset;
	}
}

template <class T>
std::shared_ptr<T> AssetManager<T>::getAsset(const std::string& id) {
	if (assetMap.find(id) == assetMap.end()) {
		return nullptr;
	}

	return assetMap[id];
}