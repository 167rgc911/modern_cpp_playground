/**
MIT License

Copyright (c) 2023 Rami Mtier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#pragma once
#include <exception>
#include <string> 
#include <array>

namespace lorem_ipsum
{
	static auto c_lines = std::to_array({
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
		" Sed non risus.",
		" Cras elementum ultrices diam.",
		" Maecenas ligula massa, varius a, semper congue, euismod non, mi.",
		" Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat.",
		"\n\nDuis semper.",
		" Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim.",
		" Pellentesque congue.",
		" Ut in risus volutpat libero pharetra tempor.",
		" Cras vestibulum bibendum augue.",
		" Praesent egestas leo in pede.",
		" Praesent blandit odio eu enim.",
		" Pellentesque sed dui ut augue blandit sodales.",
		"\n\nVestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam nibh.",
		" Mauris ac mauris sed pede pellentesque fermentum.",
		" Maecenas adipiscing ante non diam sodales hendrerit."
		"\n\nUt velit mauris, egestas sed, gravida nec, ornare ut, mi.",
		" Aenean ut orci vel massa suscipit pulvinar.",
		" Nulla sollicitudin.",
		" Fusce varius, ligula non tempus aliquam, nunc turpis ullamcorper nibh, in tempus sapien eros vitae ligula.",
		" Pellentesque rhoncus nunc et augue.",
		" Integer id felis.",
		"\n\nCurabitur aliquet pellentesque diam.",
		" Integer quis metus vitae elit lobortis egestas.",
		" Lorem ipsum dolor sit amet, consectetuer adipiscing elit.",
		" Morbi vel erat non mauris convallis vehicula.",
		" Nulla et sapien.",
		" Integer tortor tellus, aliquam faucibus, convallis id, congue eu, quam.",
		"\n\nMauris ullamcorper felis vitae erat.",
		" Proin feugiat, augue non elementum posuere, metus purus iaculis lectus, et tristique ligula justo vitae magna."
		});

	class LongLoremIpsumException : public std::exception {
		unsigned int m_size;
	public:
		LongLoremIpsumException(unsigned int size)
		{
			m_size = size;
		}

		std::string what() {
			return "Cant generate that long lorem ipsum, size: " + std::to_string(m_size) 
				+ ". Max size is: " + std::to_string(c_lines.size());
		}
	};


	std::string extend(const std::string& str, const std::string& str2) {
		return std::move(str + str2);
	}

	std::string generate_lorem_ipsum_lines_internal(unsigned int count)
	{
		if (count > 0)
		{
			return extend(generate_lorem_ipsum_lines_internal(count - 1), c_lines[count - 1]);
		}
		return "";
	}


	std::string generate_lorem_ipsum_lines(unsigned int count)
	{
		if (count > c_lines.size())
		{
			throw LongLoremIpsumException(count);
		}
		return generate_lorem_ipsum_lines_internal(count);
	}

	template<int ... T>
	struct LoremIpsumStructure
	{
		std::string get()
		{
			return "";
		}
	};

	template<int T, int ... Rest>
	struct LoremIpsumStructure<T, Rest ...> : public LoremIpsumStructure<Rest ...>
	{
		using BASE = LoremIpsumStructure<Rest ... >;

		std::string get()
		{
			return std::move(std::string(c_lines[T]) + static_cast<BASE>(*this).get());
		}
	};

	template <int N, int ... Next>
	struct GenerateLoremIpsumStructure : public GenerateLoremIpsumStructure<N - 1, N - 1, Next...>
	{ };

	template <int ... Next>
	struct GenerateLoremIpsumStructure<0, Next ... >
	{
		using type = LoremIpsumStructure<Next ... >;
	};

	template <int linesCount>
	constexpr std::string generate_lorem_ipsum_lines()
	{
		static_assert(linesCount < c_lines.size(), "Cant generate that long Lorem Ipsum");
		static_assert(linesCount > 0, "Cant generate that small Lorem Ipsum");

		typename GenerateLoremIpsumStructure<linesCount>::type lorem_ipsum;

		return lorem_ipsum.get();
	}
}