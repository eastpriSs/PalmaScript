#pragma once
#include <fstream>
#include <vector>

namespace CharDriver
{
	constexpr size_t BUFFER_SIZE = 2048;

	enum class error_code {
		file_not_open,
		succes
	};

	class CharStream
	{
	private:
		std::vector<char> chstr = std::vector<char>(BUFFER_SIZE);

	public:
		mutable std::vector<char>::iterator startChar;
		mutable std::vector<char>::iterator forwardChar;

		inline void resetPtr(std::vector<char>::iterator& p)
		{
			p = chstr.begin();
		}

		CharStream() : startChar(chstr.begin()), forwardChar(chstr.begin()) {}

	};

	namespace CharStreamStuff {
		static error_code fillCharStream(std::string& path, CharStream& stream)
		{
			using std::ifstream;

			ifstream f(path);
			if (!f)
				return error_code::file_not_open;

			while (f.get(*stream.startChar++));

			stream.resetPtr(stream.startChar);
			stream.forwardChar = stream.startChar + 1;

			return error_code::succes;
		}
	};
};
