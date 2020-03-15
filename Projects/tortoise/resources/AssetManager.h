#pragma once
#include <memory>
#include <unordered_map>

namespace tortoise {
	namespace asset {
		template<class T>
		class AssetManager {
		public:
			void addAsset(const std::string& id, std::shared_ptr<T> asset);
			std::shared_ptr<T> getAsset(const std::string& id);
		private:
			std::unordered_map<std::string, std::shared_ptr<T>> assetMap;
		};
	}
}