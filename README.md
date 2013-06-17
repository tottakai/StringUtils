StringUtils
===========

Ruby like C++ string utilities. Just include *stringutils.h* to your project to use.

Examples
-----------

**tottakai::split_map** calls the given function for all the produced substrings.

	tottakai::split_map("Little brown fox", ' ', [] (const std::string& substr) {
		std::cout << substr << std::endl;
	});


**tottakai::strip** removes leading and trailing whitespace

	tottakai::strip(" foo ") outputs "foo"

**tottakai::lstrip** removes leading whitespace

**tottakai rstrip** removes trailing whitespace

**tottakai::partition** searcher for separator in the string and returns the part before it, the separator, and the part after it.

**tottakai::rpartition** searcher for separator in the string from the end of string and returns the part before it, the separator, and the part after it.

**tottakai::each_line** calls func for every line in str.
