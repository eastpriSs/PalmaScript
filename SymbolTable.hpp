#pragma once
#include <unordered_map>
#include <string>


namespace SymbolTable
{
	namespace Identificator 
	{
		enum class typeOfIdentificator {Int128, Nope};
		
		struct IdentificatorDescription
		{
			typeOfIdentificator type = typeOfIdentificator::Nope;
			uint8_t stackOffset = 0;
			bool isDeclarated = false;
		};
		
	};
	using namespace Identificator;
	static std::unordered_map<std::string, IdentificatorDescription> symtab;

	namespace Identificator 
	{
		static bool isDeclarated(const std::string& idname) {
			return symtab.find(idname) != symtab.end();
		}
	};
};