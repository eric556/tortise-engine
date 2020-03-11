#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <string>

#ifndef MAX_COMPONENTS
#define MAX_COMPONENTS 128
#endif // !MAX_COMPONENTS


#include "Component.hpp"

namespace ECS {
	class Entity {
	public:
		unsigned int id;
		std::string name = "";

		Entity(unsigned int id = 0) {
			this->id = id;
		}

		Entity(std::shared_ptr<Entity>& parent, unsigned int id = 0) {
			this->parent = parent;
			this->id = id;
		}

		template<class T>
		std::shared_ptr<T> addComponent() {
			T comp;
			componentFlags.set(comp.type);
			components.push_back(std::shared_ptr<Component>(new T()));

			return std::static_pointer_cast<T>(components.back());
		}

		void addComponent(unsigned int flag) {
			componentFlags.set(flag);
		}

		template<class T>
		std::shared_ptr<T> getComponent() {
			T comp;

			for (int i = 0; i < components.size(); i++) {
				if (components[i]->type == comp.type) {
					return std::static_pointer_cast<T>(components[i]);
				}
			}

			return nullptr;
		}

		bool hasComponent(unsigned int flag) {
			return componentFlags.test(flag);
		}

		bool hasComponents(unsigned int flags[], int numFlags) {
			bool toReturn = true;

			for (int i = 0; i < numFlags; i++) {
				toReturn &= hasComponent(flags[i]);
			}

			return toReturn;
		}

		template<class T>
		bool hasComponent() {
			T comp;
			return componentFlags.test(comp.type);
		}

		template<class T>bool hasComponents() {
			return this->hasComponent<T>();
		}

		template<class T1, class T2, class... rest>
		bool hasComponents() {

			if (hasComponent<T1>()) {
				return true && hasComponents<T2, rest...>();
			}

			return false;
		}

		template<class T1>
		bool hasComponents(unsigned int flag) {
			if (!hasComponent(flag)) return false;

			return hasComponents<T1>();
		}

		template<class T1>
		bool hasComponents(unsigned int flags[], int numFlags) {
			if (!hasComponents(flags, numFlags)) return false;

			return hasComponents<T1>();
		}

		template<class T1, class T2, class... rest>
		bool hasComponents(unsigned int flag) {
			if (!hasComponent(flag)) return false;

			return hasComponents<T1, T2, rest...>();
		}

		template<class T1, class T2, class... rest>
		bool hasComponents(unsigned int flags[], int numFlags) {
			if (!hasComponents(flags, numFlags)) return false;

			return hasComponents<T1, T2, rest...>();
		}

		template<class T>
		bool removeComp() {
			T c;
			for (int i = 0; i < components.size(); i++) {
				if (components[i]->type == c.type) {
					componentFlags.set(c.type, false);
					components.erase(components.begin() + i);
					return true;
				}
			}

			return false;
		}

		void removeComp(unsigned int flag) {
			componentFlags.set(flag, false);
		}

		void addChild(std::shared_ptr<Entity>& child) {
			this->children.push_back(child);
		}

		bool removeChild(unsigned int id) {
			for (int i = 0; i < children.size(); i++){
				if (auto spt = children[i].lock()) {
					if (spt->id == id) {
						spt->parent = std::weak_ptr<Entity>();
						children.erase(children.begin() + i);

						return true;
					}
				}
			}

			return false;
		}


	public:
		std::vector <std::shared_ptr<Component>> components;
		std::bitset<MAX_COMPONENTS> componentFlags;
		std::vector <std::weak_ptr<Entity>> children;
		std::weak_ptr<Entity> parent;
	};
}