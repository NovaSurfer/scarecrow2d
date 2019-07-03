#include "ini_io.h"

// clang-format off
IniIO::IniIO(const std::string &filename)
{
    // Opening file
    std::ifstream file(filename);
    if(file)
    {
        std::cmatch result;

        SectionUnit unit = SectionUnit();

        for (std::string line; std::getline(file, line);)
        {
            // Check if current line have a section
            if(is_section(line, result))
            {
                std::string section_name = result.str().substr(1, result.str().size() - 2);

                if(unit.section_name != section_name)
                {
                    if(!unit.section_name.empty())
                    {
                        sections.push_back(unit);

                        unit.section_name = section_name;
                        unit.kv_pairs.clear();
                    }
                    else
                    {
                        unit.section_name = section_name;
                    }
                }
            }
                // Check if current line have a key-value pair
            else if(is_key_value(line, result))
            {
                std::pair<std::string, std::string> kvs = split_key_value(line);
                // TODO: check kvs for correctness
                unit.kv_pairs.emplace_back(kvs.first,kvs.second);
            }
        }
        // Push the last section when file ends.
        sections.push_back(unit);
        this->filename = filename;
    }
    else
    {
        throw std::runtime_error("Cannot open config file");
    }
}


std::string IniIO::get_value(const std::string &section_name, const std::string &key) const
{
    auto [s_pos, k_pos] = get_positions(section_name, key);

    if(s_pos < 0) return {};
    return sections[s_pos].kv_pairs[k_pos].second;
}

std::string IniIO::get_value(const std::string &key) const
{
    std::string value;

    for(std::size_t i = 0; i < sections.size(); i++)
    {
        ptrdiff_t k_pos = get_key_pos(key, i);
        if(k_pos >= 0){
            return sections[i].kv_pairs[k_pos].second;
        }
    }
    return {};
}

std::vector<std::pair<std::string, std::string>> IniIO::get_kvps(const std::string &section_name) const
{
    ptrdiff_t pos = get_section_pos(section_name);
    if(pos < 0) return {};
    return sections[pos].kv_pairs;
}

void IniIO::set_value(const std::string &section_name, const std::string &key, const std::string &value)
{
    auto [s_pos, k_pos] = get_positions(section_name, key);

    if (s_pos < 0) return;
    sections[s_pos].kv_pairs[k_pos].second = value;
    save_file();
}

/*void IniIO::add_value(const std::string &section_name, const std::string &key, const std::string &value)
{

}*/

// TODO: save file with previous formatting style and commentaries
void IniIO::save_file()
{
    // Opening file
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
    if(file)
    {
        for(const auto& s : sections)
        {
            file << "[" << s.section_name << "]\n";
            for(const auto& kv : s.kv_pairs)
            {
                file << kv.first << "=" << kv.second << "\n";
            }
        }
    }
    else
    {
        std::cerr << "Cannot open file " << filename << "\n";
    }
}

std::pair<ptrdiff_t, ptrdiff_t> IniIO::get_positions(const std::string &section_name, const std::string &key) const
{
    // Find section position
    ptrdiff_t s_pos = get_section_pos(section_name);
    if(s_pos >= 0){
        ptrdiff_t k_pos = get_key_pos(key, s_pos);
        if(k_pos >= 0){
            return std::make_pair(s_pos, k_pos);
        }
    }

    // If no key/section found
    return std::make_pair(-1,-1);
}

ptrdiff_t IniIO::get_section_pos(const std::string& section_name) const
{
    auto s_pos = std::find_if(
            sections.begin(),
            sections.end(),
            [&section_name](const SectionUnit& u) {
                return u.section_name == section_name;}) - sections.begin();

    if(s_pos < sections.size()){
        return s_pos;
    }
    return -1;
}

ptrdiff_t IniIO::get_key_pos(const std::string& key, ptrdiff_t section_pos) const
{
    if(section_pos < sections.size()){
        const std::vector<std::pair<std::string, std::string>>& kv_pairs = sections[section_pos].kv_pairs;

        auto k_pos = std::find_if(
                kv_pairs.begin(),
                kv_pairs.end(),
                [&key](const std::pair<std::string, std::string>& kvp) {
                    return kvp.first == key;}) - kv_pairs.begin();

        if(k_pos < kv_pairs.size())
            return k_pos;
    }
    return -1;
}

bool IniIO::is_section(std::string str, std::cmatch& results) const
{
    std::regex section_regex(R"(\[([^#;\r\n]+)\])");
    return std::regex_match(str.c_str(), results, section_regex);
}

bool IniIO::is_key_value(std::string str, std::cmatch& results) const
{
    std::regex kvp_regex(R"(([^\[\]\r\n=#;]+)=([^#;\\\r\n]*(?:\\.[^#;\\\r\n]*)*))");
    return std::regex_match(str.c_str(), results, kvp_regex);
}

std::pair<std::string, std::string> IniIO::split_key_value(std::string str) {
    // Remove whitespaces
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::string arg;
    std::string::size_type pos = str.find('=');
    if(str.npos != pos) {
        arg = str.substr(pos + 1);
        str = str.substr(0, pos);
    }
    return make_pair(str, arg);
}