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

    // Returns a copy of str with leading whitespace removed.
    std::string lstrip(const std::string& str) {
        const auto whitespace = " \t\n\v\f\r";
        const auto begin = str.find_first_not_of(whitespace);
        if (begin == std::string::npos)
            return std::string();
        const auto length = str.length() - begin;
        return str.substr(begin, length);
    }    

    // Returns a copy of str with trailing whitespace removed.
    std::string rstrip(const std::string& str) {
        const auto whitespace = " \t\n\v\f\r";
        const auto end = str.find_last_not_of(whitespace);
        if (end == std::string::npos)
            return std::string();
        return str.substr(0, end+1);
    }

    // Returns a copy of str with leading and trailing whitespace removed
    std::string strip(const std::string str) {
        const auto whitespace = " \t\n\v\f\r";
        const auto begin = str.find_first_not_of(whitespace);
        if (begin == std::string::npos)
            return std::string();

        const auto end = str.find_last_not_of(whitespace);
        const auto length = end - begin + 1;
        return str.substr(begin, length);
    }

    // Searcher for separator in the string and returns the part before it, the separator, and the part after it.
    std::tuple<std::string, char, std::string> partition(const std::string& str, char separator) {
        const auto divider = str.find_first_of(separator);
        if (divider == std::string::npos)
            return std::make_tuple(std::string(), separator, std::string());
        return std::make_tuple(str.substr(0,divider), separator, str.substr(divider+1, str.length()-divider));
    }

    // Searcher for separator in the string from the end of string and returns the part before it, the separator, and the part after it.
    std::tuple<std::string, char, std::string> rpartition(const std::string& str, char separator) {
        const auto divider = str.find_last_of(separator);
        if (divider == std::string::npos)
            return std::make_tuple(std::string(), separator, std::string());
        return std::make_tuple(str.substr(0,divider), separator, str.substr(divider+1, str.length()-divider));
    }

    // Calls func for every line in str
    void each_line(const std::string& str, std::function<void(const std::string&)> func) {
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item)) {
            func(item);
        }
    }
};

#endif