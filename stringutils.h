#ifndef TOTTAKAI_STRINGUTILS_H_
#define TOTTAKAI_STRINGUTILS_H_

namespace tottakai {
	void split_map(const std::string& s, char delim, std::function<void(const std::string&)> func) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			func(item);
		}
	}

	// Returns a copy of str with trailing whitespace removed.
	std::string rstrip(const std::string& str) {

	}

	// Returns a copy of str with leading and trailing whitespace removed
	std::string strip(const std::string str) {
		
	}
};

#endif